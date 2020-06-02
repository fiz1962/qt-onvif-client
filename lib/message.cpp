#include "message.h"
#include <QUuid>
#include <QTime>
#include <QDateTime>
#include <QStringList>
#include <QCryptographicHash>
#include <unistd.h>

using namespace ONVIF;

QDomElement ONVIF::hashToXml(const QString &name,const QHash<QString, QString> &hash) {
    QDomElement element = newElement(name);
    QHashIterator<QString, QString> i(hash);
    while(i.hasNext()) {
        i.next();
        element.appendChild(newElement(i.key(), i.value()));
    }
    return element;
}

QDomElement ONVIF::listToXml(const QString &name, const QString &itemName, const QStringList &list) {
    QDomElement element = newElement(name);
    for(int i = 0; i < list.length(); i++) {
        element.appendChild(newElement(itemName, list.at(i)));
    }
    return element;
}

QDomElement ONVIF::newElement(const QString &name, const QString &value) {
    QDomDocument doc;
    QDomElement element = doc.createElement(name);
    if(value != "") {
        QDomText textNode = doc.createTextNode(value);
        element.appendChild(textNode);
    }
    doc.appendChild(element);
    return doc.firstChildElement();
}

Message *Message::getOnvifSearchMessage() {
    QHash<QString, QString> namespaces;
    namespaces.insert("a", "http://schemas.xmlsoap.org/ws/2004/08/addressing");
    namespaces.insert("d", "http://schemas.xmlsoap.org/ws/2005/04/discovery");
    namespaces.insert("dn", "http://www.onvif.org/ver10/network/wsdl");
    Message *msg = new Message(namespaces);
    QDomElement action = newElement("a:Action", "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe");
    QDomElement message_id = newElement("a:MessageID", "uuid:" + msg->uuid());
    QDomElement to = newElement("a:To", "urn:schemas-xmlsoap-org:ws:2005:04:discovery");
    msg->appendToHeader(action);
    msg->appendToHeader(message_id);
    msg->appendToHeader(to);
    
    QDomElement probe = newElement("d:Probe");
    probe.appendChild(newElement("dn:Types", "dn:NetworkVideoTransmitter"));
    msg->appendToBody(probe);
    
    return msg;
}


Message* Message::getMessageWithUserInfo(QHash<QString, QString> &namespaces, const QString &name, const QString &passwd) {
    namespaces.insert("wsse", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");
    namespaces.insert("wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");
    Message *msg = new Message(namespaces);
    QDomElement security = newElement("wsse:Security");
    security.setAttribute("mustUnderstand", "1");
    security.setAttribute("xmlns", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");

    QString dt1 = QDateTime::currentDateTime().toTimeSpec(Qt::UTC).toString("yyyy-MM-ddThh:mm:ssZ");
    QString dt2 = QDateTime::currentDateTime().toTimeSpec(Qt::UTC).addSecs(10).toString("yyyy-MM-ddThh:mm:ssZ");

    QByteArray nonce = "KvJlNB6gDEy9fpoWx9P66iUAAAAAAA==";
    QByteArray nonce2 = nonce.fromBase64(nonce);
    nonce2 += dt1 +passwd;

    QString sha1 = QCryptographicHash::hash(nonce2, QCryptographicHash::Sha1).toBase64();

    QDomElement usernameToken = newElement("wsse:UsernameToken");
    usernameToken.setAttribute("wsu:Id", "UsernameToken-1");
    QDomElement username = newElement("wsse:Username", name);
    QDomElement password = newElement("wsse:Password", sha1);
    QDomElement nonceEl = newElement("Nonce", nonce);
    //password.setAttribute("Type", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText");
    password.setAttribute("Type", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordDigest");
    nonceEl.setAttribute("EncodingType", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-soap-message-security-1.0#Base64Binary");

    usernameToken.appendChild(username);
    usernameToken.appendChild(password);
    usernameToken.appendChild(nonceEl);
    usernameToken.appendChild(newElement("wsu:Created", dt1));

    security.appendChild(usernameToken);
    msg->appendToHeader(security);

    // pw digest doesn't like too many messages in a short time
    sleep(1);
    return msg;
}


Message::Message(const QHash<QString, QString> &namespaces, QObject *parent) : QObject(parent) {
    this->mNamespaces = namespaces;
    mDoc.appendChild(mDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\""));
    mEnv = mDoc.createElementNS("http://www.w3.org/2003/05/soap-envelope", "soap:Envelope");
    mHeader = mDoc.createElement("soap:Header");
    mBody = mDoc.createElement("soap:Body");
    mBody.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    mBody.setAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
}

QString Message::toXmlStr() {
    QHashIterator<QString, QString> i(mNamespaces);
    while (i.hasNext()) {
        i.next();
        mEnv.setAttribute("xmlns:" + i.key(), i.value());
    }
    
    mEnv.appendChild(mHeader);
    mEnv.appendChild(mBody);
    mDoc.appendChild(mEnv);
    return mDoc.toString();
}

QString Message::uuid() {
    QUuid id = QUuid::createUuid();
    return id.toString();
}

void Message::appendToBody(const QDomElement &body) {
    mBody.appendChild(body);
}

void Message::appendToHeader(const QDomElement &header) {
    mHeader.appendChild(header);
}
