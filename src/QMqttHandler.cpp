#include "QMqttHandler.h"
#include "AppConstants.h"

QMqttHandler *QMqttHandler::m_instance = nullptr;

QMqttHandler::QMqttHandler(QObject* parent)
    : QObject(parent)
{
}

QMqttHandler *QMqttHandler::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new QMqttHandler();
    }
    return m_instance;
}

QMqttHandler::~QMqttHandler()
{

}

bool QMqttHandler::loadMQTTSetting(QString path)
{
    QFile file(path.toStdString().c_str());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonArray a = QJsonDocument::fromJson(val.toUtf8()).array();

    return true;
}

int QMqttHandler::initBokerHost(QString path)
{
    broker_path = path;

    return 0;
}

void QMqttHandler::connectMQTT(QString brokerName, qint16 port)
{
    m_client = new QMqttClient(this);

    m_client->setHostname(brokerName);
    m_client->setPort(port);

    m_client->connectToHost();

    connect(m_client, &QMqttClient::connected, this, &QMqttHandler::onMQTT_Connected);
    connect(m_client, &QMqttClient::disconnected, this, &QMqttHandler::onMQTT_disconnected);
    connect(m_client, &QMqttClient::messageReceived, this, &QMqttHandler::onMQTT_Received);
}

void QMqttHandler::onMQTT_Connected()
{
    CONSOLE << "Connected to MQTT Broker";

    MQTT_Subcrib(RobotNodes.at(0));

    emit MQTTConnected();
}

void QMqttHandler::onMQTT_disconnected()
{
    CONSOLE << "Disconnected to MQTT Broker";
}

void QMqttHandler::onMQTT_Received(const QByteArray &message, const QMqttTopicName &topic)
{
    CONSOLE << "Received message: " << message << " from topic: " << topic.name();

    QJsonObject msg = QJsonDocument::fromJson(message).object();
    QString m_key = msg.keys().join(", ");
    CONSOLE << m_key;

    if(m_key == "nodes")
    {
        QJsonArray nodesArray = msg["nodes"].toArray();
        QList<QString> names;
        QList<int> xValues;
        QList<int> yValues;
        QList<int> zValues;
        int loopTime = 1;


        QJsonValue nodeValue1 = nodesArray[0];
        QJsonObject nodeObject1 = nodeValue1.toObject();
        QString name1 = nodeObject1["name"].toString();
        int x1 = nodeObject1["x"].toInt();
        int y1 = nodeObject1["y"].toInt();
        int z1 = nodeObject1["z"].toInt();

        CONSOLE << "Name:" << name1;
        CONSOLE << "X:" << x1;
        CONSOLE << "Y:" << y1;
        CONSOLE << "Z:" << z1;

        names.append(name);
        xValues.append(x);
        yValues.append(y);
        zValues.append(z);

        QJsonValue nodeValue2 = nodesArray[1];
        QJsonObject nodeObject2 = nodeValue2.toObject();
        QString name2 = nodeObject2["name"].toString();
        int x2 = nodeObject2["x"].toInt();
        int y2 = nodeObject2["y"].toInt();
        int z2 = nodeObject2["z"].toInt();

        CONSOLE << "Name:" << name2;
        CONSOLE << "X:" << x2;
        CONSOLE << "Y:" << y2;
        CONSOLE << "Z:" << z2;

        names.append(name2);
        xValues.append(x2);
        yValues.append(y2);
        zValues.append(z2);

        QJsonValue nodeValue3 = nodesArray[2];
        QJsonObject nodeObject3 = nodeValue3.toObject();
        int tmp_loop = nodeObject3["loopTime"].toString();

        if(tmp_loop < 1)
        {
            loopTime = 1;
        }
        else 
        {
            loopTime = tmp_loop;
        }

        emit mqttSubTarget(names, xValues, yValues, zValues, loopTime);
    }
    else if(m_key == "password, username")
    {
        QString username = msg.value("username").toString();
        QString password = msg.value("password").toString();

        CONSOLE << username << password;
        emit mqttSubLogin(username, password);

    }
    else
    {
        CONSOLE << msg.value(m_key).toString();
        emit mqttSubControl(msg.value(m_key).toString());
    }

    setMqttMessage(msg);

    emit MQTT_Received(m_mqttMessage);
}

void QMqttHandler::MQTT_Publish(RobotNode node, QJsonObject message)
{
    QMqttTopicName topic(node.current_state_topic);

    // this->RobotNodes.at(0).current_state_message = message;

    m_client->publish(topic, QJsonDocument(message).toJson());
}

void QMqttHandler::MQTT_Publish(QString _topic, QJsonObject message)
{
    QMqttTopicName topic(_topic);

    CONSOLE << _topic << " " << message;

    m_client->publish(topic, QJsonDocument(message).toJson());
}

void QMqttHandler::MQTT_PublishLogin(RobotNode node, QJsonObject message)
{
    QMqttTopicName topic(node.topic_login_userInforesponse);

    // this->RobotNodes.at(0).current_state_message = message;

    CONSOLE << topic;

    m_client->publish(topic, QJsonDocument(message).toJson());
}

void QMqttHandler::MQTT_Subcrib(RobotNode node)
{
    CONSOLE << node.control_topic;
    
    QMqttTopicFilter filter(node.control_topic);

    m_client->subscribe(filter);
}

void QMqttHandler::MQTT_Subcrib(QString _topic)
{
    CONSOLE << "Sub: " << _topic;
    QMqttTopicFilter filter(_topic);
    m_client->subscribe(filter);
}

void QMqttHandler::setMqttMessage(QJsonObject &msg)
{

}

void QMqttHandler::setCurrentRobotNode(RobotNode node)
{
    
}