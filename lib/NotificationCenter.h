#ifndef EXTRAS_NOTIFICATIONCENTER_NOTIFICATIONCENTER_H
#define EXTRAS_NOTIFICATIONCENTER_NOTIFICATIONCENTER_H

#include <QObject>
#include <QString>
#include <QImage>


namespace Djbozkosz {
namespace Extras {
namespace NotificationCenter
{
	struct Activity
	{
		public: // types

		struct EBadgeType { enum Enum
		{
			None = 0,
			Indeterminate,
			Number
		};};

		public: // members

		QString          Name;
		QString          Title;
		QString          SubTitle;
		QImage           MaskIcon;
		QString          MaskIconName;
		EBadgeType::Enum BadgeType;
		int              BadgeNumber;
		bool             UseNotification;
		bool             UsePopup;
		bool             UseLockScreen;
		bool             OpenAppOnTap;
		QString          UserData;

		QString          Reserved0;
		QString          Reserved1;
		QString          Reserved2;

		public: // methods

		explicit inline Activity() :
			BadgeType(EBadgeType::None),
			BadgeNumber(0),
			UseNotification(true),
			UsePopup(true),
			UseLockScreen(true),
			OpenAppOnTap(true)
		{
		}

		explicit inline Activity(
			const QString&   name,
			const QString&   title,
			const QString&   subTitle,
			const QImage&    maskIcon,
			const QString&   maskIconName,
			EBadgeType::Enum badgeType,
			int              badgeNumber,
			bool             useNotification,
			bool             usePopup,
			bool             useLockScreen,
			bool             openAppOnTap,
			const QString&   userData) :
			Name(name),
			Title(title),
			SubTitle(subTitle),
			MaskIcon(maskIcon),
			MaskIconName(maskIconName),
			BadgeType(badgeType),
			BadgeNumber(badgeNumber),
			UseNotification(useNotification),
			UsePopup(usePopup),
			UseLockScreen(useLockScreen),
			OpenAppOnTap(openAppOnTap),
			UserData(userData)
		{
		}

		virtual inline ~Activity() {}
	};


	struct Notification : public Activity
	{
		public: // members

		bool    OverrideFormat;
		int     StatusIcon;
		bool    UseDialog;
		bool    UseLight;
		bool    UseAudio;
		QString AudioPath;
		bool    UseVibration;
		bool    CloseOnTap;
		int     SecondsFromNow;

		public: // methods

		explicit inline Notification() :
			Activity(),
			OverrideFormat(false),
			StatusIcon(-1),
			UseDialog(true),
			UseLight(true),
			UseAudio(true),
			UseVibration(true)
		{
		}

		explicit inline Notification(
			const QString&   name,
			const QString&   title,
			const QString&   subTitle,
			const QImage&    maskIcon,
			const QString&   maskIconName,
			EBadgeType::Enum badgeType,
			int              badgeNumber,
			bool             useNotification,
			bool             usePopup,
			bool             useLockscreen,
			bool             openAppOnTap,
			const QString&   userData,
			bool             overrideFormat,
			int              statusIcon,
			bool             useDialog,
			bool             useLight,
			bool             useAudio,
			const QString&   audioPath,
			bool             useVibration,
			bool             closeOnTap,
			int              secondsFromNow) :
			Activity(
				name,
				title,
				subTitle,
				maskIcon,
				maskIconName,
				badgeType,
				badgeNumber,
				useNotification,
				usePopup,
				useLockscreen,
				openAppOnTap,
				userData),
			OverrideFormat(overrideFormat),
			StatusIcon(statusIcon),
			UseDialog(useDialog),
			UseLight(useLight),
			UseAudio(useAudio),
			AudioPath(audioPath),
			UseVibration(useVibration),
			CloseOnTap(closeOnTap),
			SecondsFromNow(secondsFromNow)
		{
		}

		virtual inline ~Notification() {}
	};


	class NotificationCenter : public QObject
	{
		private:

		Q_OBJECT

		public: // types

		struct EPermission { enum Enum
		{
			Declined = 0,
			Granted,
			Undefined
		};};

		public: // methods

		explicit NotificationCenter();
		virtual ~NotificationCenter();

		bool IsInitialized() const;

		void HasPermission();
		void RequestPermission(const QImage& maskIcon);

		void AddOrUpdate(const Activity& activity);
		void AddOrUpdate(const Notification& notification);
		void Remove(const QString& name);
		void Clear();

		signals: // interface

		void HasPermissionResult    (NotificationCenter::EPermission::Enum permission);
		void RequestPermissionResult(NotificationCenter::EPermission::Enum permission);
		void NotificationOpened     (const Activity& activity);

		private slots:

#ifdef Q_OS_SYMBIAN
		void HandleHasPermissionResult    (NotificationCenter::EPermission::Enum permission);
		void HandleRequestPermissionResult(NotificationCenter::EPermission::Enum permission);
		void HandleNotificationOpened     (const Activity& activity);
#endif
	};

#ifndef Q_OS_SYMBIAN
	inline      NotificationCenter::NotificationCenter()             {}
	inline      NotificationCenter::~NotificationCenter()            {}
	inline bool NotificationCenter::IsInitialized() const { return false; }
	inline void NotificationCenter::HasPermission()                  {}
	inline void NotificationCenter::RequestPermission(const QImage&) {}
	inline void NotificationCenter::AddOrUpdate(const Activity&)     {}
	inline void NotificationCenter::AddOrUpdate(const Notification&) {}
	inline void NotificationCenter::Remove(const QString&)           {}
	inline void NotificationCenter::Clear()                          {}
#endif
}}}

#endif // EXTRAS_NOTIFICATIONCENTER_NOTIFICATIONCENTER_H
