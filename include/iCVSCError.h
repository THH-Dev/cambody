#ifndef __IC_ERROR_H__
#define __IC_ERROR_H__

// Non-critical error, no need to release the channel, reconnect; critical error need to release the channel, reconnect.

#define IC_SUCCESS							0		/* Operation success */
#define IC_ERROR							-1		// Unknown error

#define IC_ERROR_INITIALIZED				1		// Initialized
#define IC_ERROR_UNINITIALIZED				2		// Uninitialized
#define IC_ERROR_INIT_SOCKET_FAILED			3		// Initialize network protocol stack failed
#define IC_ERROR_MALLOC						4		// Memory allocation error
#define IC_ERROR_SESSION_HANDLE				5		// Illegal session handle
#define IC_ERROR_PU_HANDLE					6		// Illegal device handle
#define IC_ERROR_RESOURCE_HANDLE			7		// Illegal resource handle
#define IC_ERROR_STREAM_HANDLE				8		// Illegal stream handle
#define IC_ERROR_INVALID_ADDRESS			9		// Address format error
#define IC_ERROR_PARSER_RESPONSE			10		// Parsing response message error
#define IC_ERROR_RESPONSE_FORMAT			11		// Response message foramt error
#define IC_ERROR_RESOURCE_TYPE				12		// Wrong resource type
#define IC_ERROR_BUFFER_LACK				13		// Out of buffers
#define IC_ERROR_PARAM						14		// Wrong input parameter
#define IC_ERROR_CREATE_DATA_CHANNEL		15		// Failed to create data channel
#define IC_ERROR_CREATE_NCS					16		// Failed to create NCS module
#define IC_ERROR_CREATE_DCS					17		// Failed to create DCS module
#define IC_ERROR_SERVER_STATUS				18		// Server status error
#define IC_ERROR_REPORT_FORMAT				19		// Wrong format of reported message 
#define IC_ERROR_UNSUPPORT_REQ				20		// Unsupported request
#define IC_ERROR_DOMAINNAME_TO_IP			21		// Domain name resolution failed
#define IC_ERROR_ADD_RESOURCE				22		// Resource creation failed
#define IC_ERROR_OUT_OF_USE					23		// Out of use period
// Error code returned by the front-end device
#define IC_ERROR_CONSISTENT					1001	// Setting value not in range (returned when setting configuration)
#define IC_ERROR_UNSUPPORT					1002	// Operation not supported (set configuration, return when getting configuration or control command)
#define IC_ERROR_READ						1003	// Parameter error (returned when controlling command)
#define IC_ERROR_AUTHORIZE					1004	// Message format error (returned when setting configuration and control commands)
#define IC_ERROR_OVERLAP					1005	// Resource type error (returned when controlling command)
#define IC_ERROR_OVERFLOW					1006	// Operation failed (returned while setting configuration or control command)
#define IC_ERROR_INVALID_RES				1007	// Operation has no permissions (returns when controlling a command)
#define IC_ERROR_INVALID_PARAM				1008	// The channel is not online (this value is returned when the NVR IPC channel is not online)
#define IC_ERROR_INVALID_FORMAT				1009	// Function failure (returns this when the corresponding function program exits)
#define IC_ERROR_TIME_OUT					1010	// Function timeout (returns this when forwarding a command to a function and waiting for the response to timeout)
#define IC_ERROR_DEVICE_BUSY				1012	// The equipment is busy
#define IC_ERROR_CAMERA_NOTCONFIG			1013	// Channel not configured
#define IC_ERROR_VIDEO_PRIVATE				1014	// Privacy protection


#define IC_ERROR_ROUTE_MODE					1501	// Router mode causes the application stream to fail
#define IC_ERROR_STREAM_DISABLE				1502	// The application stream failed because the stream was disabled
#define IC_ERROR_FLOW_LIMIT					1503	// Traffic restriction causes application stream to fail
#define IC_ERROR_TIME_LIMIT					1504	// Application flow fails due to time limit
#define IC_ERROR_NO_RULE					1505	// Commands have no forwarding relationship
#define IC_ERROR_PTZ_LOCKED					1506	// PTZ has been locked


// Error code returned by the service
#define IC_ERROR_NU_FORMAT					2001	// Wrong message format
#define IC_ERROR_NU_PARAM					2002	// Wrong parameter (property value)
#define IC_ERROR_UNSUPPORTOPERATION			2003	// Unsupported operations
#define IC_ERROR_DESTINATION				2004	// Target authentication failure, generally the target net element write wrong
#define IC_ERROR_PRIORITY					2005	// The priority authentication fails, the higher level user is using the resource, and the competing resource fails to report an error
#define IC_ERROR_EPID						2006	// EPID authentication failed. EPID was miswritten
#define IC_ERROR_NOOPTPERMISSION			2007	//  operation authorization failed, the user did not assign the operation permission
#define IC_ERROR_NORESPERMISSION			2008	// Resource authentication failed. Some devices cannot access the resource
#define IC_ERROR_NU_TIMEOUT					2009	// Command timeout
#define IC_ERROR_ROUTEFAILED				2010	// Routing failure
#define IC_ERROR_NOOBJPERMISSION			2011	// No object operation permissions
#define IC_ERROR_OBJNOTEXIST				2012	// Object does not exist
#define IC_ERROR_OBJALREADYEXIST			2013	// Object already exists
#define IC_ERROR_USERFULL					2014	// Exceeded the maximum number of supported users
#define IC_ERROR_USEROPTOVERFLOW			2015	// The set of operations supported by the target user is too large
#define IC_ERROR_LOWPRIORITY				2016	// Priority is not enough
#define IC_ERROR_TOKENNOTEXSIT				2017	// The requested token does not exist
#define IC_ERROR_NOVALIDDISPATCHER			2018	// No distribution units are available
#define IC_ERROR_AUDIO_CHANNEL_OCCUPY		2019	// The audio output channel is occupied
#define IC_ERROR_MR_PASSWORD_INCORRECT		2020	// Incorrect password for meeting room
#define IC_ERROR_INVALIDRES					2021	// Illegal resources
#define IC_ERROR_STREAMOVERLOADED			2022	// Exceeding the maximum stream forwarding load
#define IC_ERROR_NOVALIDCSS					2023	// No cloud storage services are available
#define IC_ERROR_NORECORD					2024	// There is no video on demand
#define IC_ERROR_INVALIDVODID				2025	// Illegal ID for demand

#define IC_ERROR_VS							-2100	// VS unknown error
#define IC_ERROR_VS_NOVTDU					-2201	// VS has no distribution unit ID available
#define IC_ERROR_VS_WRONGPSW				-2202	// VS Password mistake
#define IC_ERROR_VS_UNSUPPORTOPERATION		-2203	//Error ID not supported by VS
#define IC_ERROR_VS_TOKENNOTEXIST			-2204	// VS Token does not exist
#define IC_ERROR_VS_ROUTEFAILED				-2205	// VS routing failure
#define IC_ERROR_VS_WRONGSYNCSTATUS			-2206	// Cell state out-of-sync ID in VS

// The command channel returns an error code
#define	IC_ERROR_MC_WOULDBLOCK				3001	// Operation is in progress
#define IC_ERROR_MC_PARAM					3002	// Function parameter error
#define	IC_ERROR_REQTIMEOUT					3003	// The request timeout
#define IC_ERROR_STATUS						3004	// State error
#define IC_ERROR_NOEXTPARAM					3005	// No extension parameter
#define	IC_ERROR_UNKOWN						-3001	// Undefined error. not return normally 
#define	IC_ERROR_SOCKETCONNECT				-3002	// SOCKET Connection error
#define	IC_ERROR_CONTIMEOUT					-3003	// Connection timeout
#define IC_ERROR_MC_MALLOC					-3004	// Memory allocation error
#define IC_ERROR_SENDDATA					-3005	// Error sending data
#define IC_ERROR_RECVDATA					-3006	// Error receiving data
#define IC_ERROR_STOP						-3007	// Operation aborted
#define IC_ERROR_NOROUTE					-3008	// Routing failure
#define IC_ERROR_NOSERVER					-3009	// Service not enabled
#define IC_ERROR_UNREACHABLE				-3010	// Unreachable address
#define IC_ERROR_EXTPARAMLEN				-3104	// An extension parameter length error was returned during registration
#define IC_ERROR_HTTPHEADNOCONTENT			-3108	// Registration returns no content-length in the HTTP header
#define IC_ERROR_HTTPHEADOVERFLOW			-3109	// The content-length overflow in the HTTP header is returned when registering
#define IC_ERROR_HTTPCONTENTNOXMLHEAD		-3110	// Registration returns no XML header in the HTTP content
#define IC_ERROR_HTTPCONTENTXMLFORMAT		-3111	// An XML format error was returned in the HTTP content during registration
#define IC_ERROR_REDIRECTRESULT				-3112	// Error in result of redirected message returned during registration
#define IC_ERROR_REDIRECTVERSION			-3113	//The challenge message returned during registration has the wrong version number
#define IC_ERROR_SYNCFLAG					-3201	// Beginning character error when receive command 
#define IC_ERROR_VERSION					-3202	// Version error when receive command
#define IC_ERROR_CTRLFLAG					-3203	// Control field error while receiving command
#define IC_ERROR_MSGTYPE					-3204	// Error message type when receiving command
#define IC_ERROR_PACKETLEN					-3205	// Packet length error when receiving command
#define IC_ERROR_PACKETTYPE					-3206	// Wrong package type when receiving command
#define IC_ERROR_BODYLEN					-3207	// When receiving a command, the inclusion length is not an 8-byte integer multiple
#define IC_ERROR_REGISTER_UNKOWN			-3299	// Returns an unknown error when registering,-1 and other values that are not in range
#define IC_ERROR_VERIFY_USERNOTEXIST		-3301	// The user does not exist
#define IC_ERROR_VERIFY_USERINACTIVE		-3302	// The user is disabled
#define IC_ERROR_VERIFY_EPIDINACTIVE		-3303	// EPID is disabled
#define IC_ERROR_VERIFY_PASSWORDWRONG		-3306	// Password error
#define IC_ERROR_VERIFY_USBKEYINVALID		-3307	// Invalid USBKey
#define IC_ERROR_VERIFY_USERFULL			-3308	// The users are full
#define IC_ERROR_VERIFY_TIMEOUT				-3309	// Authentication timeout
#define IC_ERROR_VERIFY_ROUTEFAILED			-3310	// Routing failure
#define IC_ERROR_VERIFY_AUTHKEYINVALID		-3311	// Invalid AuthKey
#define IC_ERROR_VERIFY_EPONLINEUSERFULL	-3312	//The maximum number of online users exceeding the corporate limit
#define IC_ERROR_VERIFY_USERLOCKED3			-3313	// The user has been locked due to multiple incorrect passwords. Please try again after 3 minutes
#define IC_ERROR_VERIFY_WRONGACCOUNTORPSW4	-3381	// User name or password error. there are 4 more chances
#define IC_ERROR_VERIFY_WRONGACCOUNTORPSW3	-3382	// User name or password error. there are 3 more chances
#define IC_ERROR_VERIFY_WRONGACCOUNTORPSW2	-3383	// User name or password error. there are 2 more chances
#define IC_ERROR_VERIFY_WRONGACCOUNTORPSW1	-3384	// User name or password error. there are 1 more chances
#define IC_ERROR_VERIFY_USERLOCKED24		-3385	// User has been locked due to multiple incorrect passwords input. Please try again 24 hours later

#define IC_ERROR_REDIRECT_UNKOWN			-3499	// Returns an unknown error,-1, and other values not in range when redirected
#define IC_ERROR_MC_FORMAT					-3501	// Message format error
#define IC_ERROR_UNSUPPORT_TERMINAL_TYPE	-3502	// Unsupported terminal types
#define IC_ERROR_NONE_ONLINE				-3503	// There is no online PUI or CUI
#define IC_ERROR_NONE_SUPPORT_REDIRECT		-3504	// CUI does not support redirection
#define IC_ERROR_UNSUPPORT_PRUDUCER_ID		-3505	// This vendor ID is not supported
#define IC_ERROR_OPERATION_WOULDBLOCK		-3510	// The operation cannot be completed temporarily

// 数据通道返回错误码
#define IC_ERROR_DC_WOULDBLOCK				4001	// The operation cannot be completed temporarily
#define IC_ERROR_FRAMEBUF_LEN				4002	// Frame length error
#define IC_ERROR_END						4003	// Receive an end package, such as download complete,etc.
#define IC_ERROR_UNKNOW						-4001	// Undefined error. not return normally 
#define IC_ERROR_DC_PARAM					-4002	// Parameter error
#define IC_ERROR_IVALHANDLE					-4003	// Invalid handle
#define IC_ERROR_DC_MALLOC					-4004	// Memory error
#define IC_ERROR_DC_TIMEOUT					-4005	// Timeout
#define IC_ERROR_CONNECT					-4006	// Connection error
#define IC_ERROR_TCPSEND					-4007	// TCP sending error
#define IC_ERROR_TCPRECV					-4008	// TCP receiving error
#define IC_ERROR_TCPCLOSE					-4009	// TCP shutdown proactively 
#define IC_ERROR_UDP						-4010	// UDP network error
#define IC_ERROR_DISCARD					-4011	// Received a disconnection command
#define IC_ERROR_DC_UNSUPPORT				-4012	// Operation not supported
#define IC_ERROR_NOTINIT					-4013	// Not initialized
#define IC_ERROR_INVTOKEN					-4101	// Invalid token 
#define IC_ERROR_CHTYPEERR					-4102	// Channel type error
#define IC_ERROR_CHEXIST					-4103	// The channel already exists
#define IC_ERROR_PACKET_VER					-4201	// Package version error
#define IC_ERROR_PACKET_TYPE				-4202	// Package type error
#define IC_ERROR_PACKET_LEN					-4203	// Package length error
#define IC_ERROR_PACKET_BFLAG				-4204	// Wrong frame start flag
#define IC_ERROR_PACKET_EFLAG				-4205	// End of frame flag error
#define IC_ERROR_FRAME_TYPE					-4211	// Frame type error
#define IC_ERROR_FRAME_LEN					-4212	//Data frame length error
// The command channel returns an error code
#define IC_ERROR_NCS_WOULDBLOCK				20001	// Operation is still in progress
#define IC_ERROR_NCS_OK						20000	// Success
#define IC_ERROR_NCS_PARAM					-20001	// Wrong parameter passed in
#define IC_ERROR_NCS_TIMEOUT				-20002	// timeout
#define IC_ERROR_NCS_TCPRECV				-20003	// TCP receive error
#define IC_ERROR_NCS_POSTLEN				-20004	// Post Message is too long
#define IC_ERROR_NCS_POST					-20005	// Post Wrong message format
#define IC_ERROR_NCS_TCPSEND				-20006	// TCP sending error
#define IC_ERROR_NCS_CHALLENGE				-20007	// Challenge failure
#define IC_ERROR_NCS_CERTIFY				-20008	// Authentication failed
#define IC_ERROR_NCS_DATA					-20009	// Data connections are not accepted
#define IC_ERROR_NCS_UNKNOWN				-20010	// Unknown error
// The data channel returns an error code
#define IC_ERROR_DCS_END			        21003	// Received empty packet
#define IC_ERROR_DCS_FARAMEBUFLEN	        21002	// Frame length error
													// This indicates that the received frame length is greater than the maximum length passed in by DSS_RecvFrame
													// The top layer should either expand the buffer or handle it accordingly
#define IC_ERROR_DCS_WOULDBLOCK				21001	// The operation is still in progress
#define IC_ERROR_DCS_OK		 				21000	// Operation success
#define IC_ERROR_DCS_MALLOC					-21001	// Memory allocation error
#define IC_ERROR_DCS_MC						-21002	// MC channel error
#define IC_ERROR_DCS_CMD					-21003  // Command response error, including response not conforming, or error returned by another server
#define IC_ERROR_DCS_PARAM					-21004	// Parameter error
#define IC_ERROR_DCS_DTC					-21007	// DTC channel error
#define IC_ERROR_DCS_TIMEOUT				-21008	// Timeout
#define IC_ERROR_DCS_TRANSID				-21009	// Illegal thing number
#define IC_ERROR_DCS_UNKNOW					-21010	// Unknown error
#define IC_ERROR_DCS_NATPROBE				-21011	// NAT Through failure

#endif /* __IC_ERROR_H__ */
