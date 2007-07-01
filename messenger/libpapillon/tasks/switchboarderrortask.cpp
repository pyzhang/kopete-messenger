namespace Papillon
{
class SwitchboardErrorMessageTask::Private
{
public:
	Private()
	{}
};

SwitchboardErrorMessageTask::SwitchboardErrorMessageTask(Task *parent)
 : Papillon::Task(parent), d(new Private)
{
}


SwitchboardErrorMessageTask::~SwitchboardErrorMessageTask()
{
	delete d;
}

/* 
 * handler error
 * See http://www.hypothetic.org/docs/msn/basics.php for a description of all error codes.
 */
void SwitchboardErrorMessageTask::handlerError()
{
	kDebug(14140) << k_funcinfo << endl;
	switch( code )
	{
		case 208:
		{
			QString msg = i18n( "Invalid user:\n"
				"this MSN user does not exist; please check the MSN ID." );
			//KMessageBox::queuedMessageBox( Kopete::UI::Global::mainWidget(), KMessageBox::Error, msg, i18n( "MSN Plugin" ) );
			emit errorMessage( MSNSocket::ErrorNormal, msg );
			userLeftChat(m_msgHandle , i18n("user never joined"));
			break;
		}
		case 215:
		{
			QString msg = i18n( "The user %1 is already in this chat.", m_msgHandle );
			//KMessageBox::queuedMessageBox( Kopete::UI::Global::mainWidget(), KMessageBox::Error, msg, i18n( "MSN Plugin" ) );
			emit errorMessage( MSNSocket::ErrorNormal, msg );
			//userLeftChat(m_msgHandle , i18n("user was twice in this chat") ); //(the user shouln't join there
			break;
		}
		case 216:
		{
			QString msg = i18n( "The user %1 is online but has blocked you:\nyou can not talk to this user.", m_msgHandle );
			//KMessageBox::queuedMessageBox( Kopete::UI::Global::mainWidget(), KMessageBox::Information, msg, i18n( "MSN Plugin" ) );
			emit errorMessage( MSNSocket::ErrorInformation, msg );
			userLeftChat(m_msgHandle, i18n("user blocked you"));
			break;
		}
		case 217:
		{
			// TODO: we need to know the nickname instead of the handle.
			QString msg = i18n( "The user %1 is currently not signed in.\n" "Messages will not be delivered.", m_msgHandle );
			//KMessageBox::queuedMessageBox( Kopete::UI::Global::mainWidget(), KMessageBox::Error, msg, i18n( "MSN Plugin" ) );
			emit errorMessage( MSNSocket::ErrorNormal, msg );
			userLeftChat(m_msgHandle, i18n("user disconnected"));
			break;
		}
		case 713:
		{
			QString msg = i18n( "You are trying to invite too many contacts to this chat at the same time" );
			//KMessageBox::queuedMessageBox( Kopete::UI::Global::mainWidget(), KMessageBox::Information, msg, i18n( "MSN Plugin" ) );
			emit errorMessage( MSNSocket::ErrorInformation, msg );
			userLeftChat(m_msgHandle, i18n("user blocked you"));
			break;
		}
		default:
			ErrorMessageTask::handleError( code, id );
			break;
	}

}

}
#include "switchboarderrortask.moc"
