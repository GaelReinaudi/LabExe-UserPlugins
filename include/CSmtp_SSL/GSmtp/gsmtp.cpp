#include "gsmtp.h"
#include "CSmtp.h"

GSmtp::GSmtp()
{
	CSmtp mail;

	mail.SetSMTPServer("", 587);
	mail.SetSecurityType(CSmtp::USE_TLS);
	mail.SetLogin("");
	mail.SetPassword("");
	mail.SetSenderName("TestLabExe");
	mail.SetSenderMail("");
	mail.SetReplyTo("");
	mail.SetSubject("The test message");
	mail.AddRecipient("");
	mail.SetXPriority(XPRIORITY_NORMAL);
	mail.SetXMailer("The Bat! (v3.02) Professional");
	mail.AddMsgLine("Hello,");
	mail.AddMsgLine("");
	mail.AddMsgLine("How are you today?");
	mail.AddMsgLine("");
	mail.AddMsgLine("Regards");
	mail.AddMsgLine("--");
	mail.AddMsgLine("User");
}

GSmtp::~GSmtp()
{

}
