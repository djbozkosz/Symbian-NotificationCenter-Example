#include <QApplication>
#include <QPushButton>

#include "Client.h"

#define null NULL
#define unused(...)   (void)(__VA_ARGS__)
#define as(obj, ...)  dynamic_cast<__VA_ARGS__>(obj)
#define is(obj, ...)  (as(obj, __VA_ARGS__) != null)


using namespace Djbozkosz::Application::Framework;


int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	Client client;
	client.showMaximized();

	return application.exec();
}


Client::Client() :
	QWidget(),
	m_Notifications(null),
	m_GridLayout(null),
	m_Log(null)
{
	m_GridLayout = new QGridLayout(this);
	setLayout(m_GridLayout);

	CreateButton("Initialize",                 0, 0, true,  SLOT(Initialize()));
	CreateButton("Is Initialized",             0, 1, false, SLOT(IsInitialized()));
	CreateButton("Has permission",             1, 0, false, SLOT(HasPermission()));
	CreateButton("Request permission",         1, 1, false, SLOT(RequestPermission()));
	CreateButton("Add or update activity",     2, 0, false, SLOT(AddOrUpdateActivity()));
	CreateButton("Add or update notification", 2, 1, false, SLOT(AddOrUpdateNotification()));
	CreateButton("Remove",                     3, 0, false, SLOT(Remove()));
	CreateButton("Clear",                      3, 1, false, SLOT(Clear()));

	m_Log = new QTextEdit(this);
	m_Log->setReadOnly(true);
	m_GridLayout->addWidget(m_Log, 4, 0, 1, 2);

	m_MaskIcon = QImage(":/images/icons/notification.png");
}

Client::~Client()
{
	m_Notifications->deleteLater();
}

void Client::Initialize()
{
	if (m_Notifications != null)
		return;

	m_Log->append("Initializing");

	m_Notifications = new NotificationCenter();

	EnableButton(0, 1);

	if (m_Notifications->IsInitialized() == false)
	{
		m_Log->append("Not Initialized");
		return;
	}

	connect(m_Notifications, SIGNAL(HasPermissionResult    (NotificationCenter::EPermission::Enum)), this, SLOT(HasPermissionResult    (NotificationCenter::EPermission::Enum)));
	connect(m_Notifications, SIGNAL(RequestPermissionResult(NotificationCenter::EPermission::Enum)), this, SLOT(RequestPermissionResult(NotificationCenter::EPermission::Enum)));
	connect(m_Notifications, SIGNAL(NotificationOpened     (Activity)),                              this, SLOT(NotificationOpened     (Activity)));

	EnableButton(1, 0);
	EnableButton(1, 1);
	EnableButton(2, 0);
	EnableButton(2, 1);
	EnableButton(3, 0);
	EnableButton(3, 1);

	m_Log->append("Initialized");
}

bool Client::IsInitialized() const
{
	auto isInitialized = (m_Notifications != null) ? m_Notifications->IsInitialized() : false;

	m_Log->append(QString("Is initialized: %1").arg(isInitialized));

	return isInitialized;
}

void Client::HasPermission()
{
	if (m_Notifications == null)
		return;

	m_Log->append("Has permissions");

	m_Notifications->HasPermission();
}

void Client::RequestPermission()
{
	if (m_Notifications == null)
		return;

	m_Log->append("Request permissions");

	m_Notifications->RequestPermission(m_MaskIcon);
}

void Client::AddOrUpdateActivity()
{
	if (m_Notifications == null)
		return;

	m_Log->append("Add or update activity");

	m_Notifications->AddOrUpdate(Activity(
		"Main", "Title", "Sub title", m_MaskIcon, "",
		Activity::EBadgeType::None, 0, true, true, true, true,
		"{ \"key\" : \"value\" }"
	));
}

void Client::AddOrUpdateNotification()
{
	if (m_Notifications == null)
		return;

	m_Log->append("Add or update notification");

	m_Notifications->AddOrUpdate(Notification(
		"Main", "Test Application", "Hello world", m_MaskIcon, "",
		Activity::EBadgeType::Number, 1, true, true, true, true,
		"{ \"key\" : \"value\" }",
		false, 69, true, true, true, "", true, true, 10
	));
}

void Client::Remove()
{
	if (m_Notifications == null)
		return;

	m_Log->append("Remove activity");

	m_Notifications->Remove("Main");
}

void Client::Clear()
{
	if (m_Notifications == null)
		return;

	m_Log->append("Clear all activities");

	m_Notifications->Clear();
}

void Client::HasPermissionResult(NotificationCenter::EPermission::Enum permission)
{
	m_Log->append(QString("Has permissions result: %1").arg(permission));
}

void Client::RequestPermissionResult(NotificationCenter::EPermission::Enum permission)
{
	m_Log->append(QString("Request permissions result: %1").arg(permission));
}

void Client::NotificationOpened(const Activity& activity)
{
	QString type("Activity");

	if (is(&activity, const Notification*) == true)
	{
		type = "Notification";
	}

	m_Log->append(QString("%1 opened: %2, %3").arg(type, activity.Name, activity.UserData));
}

void Client::CreateButton(const QString& name, int x, int y, bool enabled, const char* slot)
{
	auto button = new QPushButton(this);
	button->setText(name);
	button->setEnabled(enabled);
	connect(button, SIGNAL(clicked()), this, slot);

	m_GridLayout->addWidget(button, x, y);
}

void Client::EnableButton(int x, int y)
{
	auto layout = m_GridLayout->itemAtPosition(x, y);
	auto button = layout->widget();
	button->setEnabled(true);
}
