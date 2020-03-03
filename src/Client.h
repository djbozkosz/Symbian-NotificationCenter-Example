#ifndef APPLICATION_FRAMEWORK_CLIENT_H
#define APPLICATION_FRAMEWORK_CLIENT_H

#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QImage>

#include <lib/NotificationCenter.h>


namespace Djbozkosz {
namespace Application {
namespace Framework
{
	using namespace Djbozkosz::Extras::NotificationCenter;


	class Client : public QWidget
	{
		private:

		Q_OBJECT

		private: // members

		NotificationCenter* m_Notifications;

		QGridLayout*        m_GridLayout;
		QTextEdit*          m_Log;
		QImage              m_MaskIcon;

		public: // methods

		explicit Client();
		virtual ~Client();

		private slots: // handlers

		void Initialize();
		bool IsInitialized() const;
		void HasPermission();
		void RequestPermission();
		void AddOrUpdateActivity();
		void AddOrUpdateNotification();
		void Remove();
		void Clear();

		void HasPermissionResult    (NotificationCenter::EPermission::Enum permission);
		void RequestPermissionResult(NotificationCenter::EPermission::Enum permission);
		void NotificationOpened     (const Activity& activity);

		private: // methods

		void CreateButton(const QString& name, int x, int y, bool enabled, const char* slot);
		void EnableButton(int x, int y);
	};
}}}

#endif // APPLICATION_FRAMEWORK_CLIENT_H
