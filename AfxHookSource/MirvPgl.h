#pragma once

#define AFX_MIRV_PGL

#ifdef AFX_MIRV_PGL

/*

Changes from version 0 to version 1:
- "cam" uses all Float (instead of Double) now.
- "mirv_pgl url" sets / gets the url to use, "mirv_pgl start" doesn't take parameters anymore.


Usage:


It is a good idea to run with the FPS limited (either by vsync or by fps_max).
Otherwise the network / server will be flooded with "cam" messages or the send buffer will overflow eventually, since there is currently no throttling at all implemented so far.


Console commands:

mirv_pgl url [<url>] - Set the server's URL, example: mirv_pgl url "ws://localhost:31337/mirv"
mirv_pgl start - (Re-)Starts connectinion to server.
mirv_pgl stop - Stops connection to server.

It is safe to exec mirv_pgl stop from the server, but how will you reconnect then?


Example server:

An example server is located in misc/mirv_pgl_test/server.js


Connection loss:

If the connection is lost and not stopped, it is retried every 5 seconds.
The server-side state should be reset upon connection loss (as if mirv_pgl stop had been called).


Messages:
  The messages are exchanged as binary frames.

  Multiple messages can be in a single frame!!!!

  The message data is not aligned / padded!

  CString is a null-terminated string as in C-Language.


Messages sent to server:

"hello"
Purpose:
  Is sent upon (re)-connecting.
  If received with unexpected version, server should close the connection.
Format:
  CString cmd = "hello"
  UInt32 version = 1;

"levelInit"
Purpose:
  Is sent if in a level upon (re)-connecting after "hello" message or if a new level is loaded.
Format:
  CString cmd = "levelInit"
  CString levelName;

"levelShutdown"
Purpose:
  Is sent after "levelInit" when level is shut down.
Format:
  CString cmd = "levelShutdown"

"cam"
Purpose:
  Is sent after "levelInit" after the frame has been presented on screen.
  The data content is from when the frame presented has been calculated by the engine.
  The fov is currently automatically converted according to Alien Swarm SDK (suitable for CS:GO).
Format:
  CString cmd = "cam";
  Float time;
  Float xPosition;
  Float yPosition;
  Float zPoisiton;
  Float xRotation;
  Float yRotation;
  Float zRotation;
  Float fov;


Messages received:

"exec"
Purpose:
  Schedules cmds for console execution.
  Use with CAUTION: Flooding the client with too many commands will crash the game. Also don't use mirv_pgl start / stop (will cause deadlock).
Format:
  CString cmd = "exec";
  CString cmds;


Ideas for the future:
- Implement black image command with feedback when presented.
- Implement white image command with feedback when presented.
- Implement optional time-code (float) graphic overlay at top of screen, this would allow syncing the images and the camdata on remote PC perfectly (as long as turned on).

*/

namespace MirvPgl
{
	struct CamData
	{
		float Time = 0;
		float XPosition = 0;
		float YPosition = 0;
		float ZPosition = 0;
		float XRotation = 0;
		float YRotation = 0;
		float ZRotation = 0;
		float Fov = 90;

		CamData();
		CamData(float time, float xPosition, float yPosition, float zPosition, float xRotation, float yRotation, float zRotation, float fov);
	};

	void Init();
	void Shutdown();

	void Url_set(char const * url);
	char const * Url_get(void);

	void Start();
	void Stop();
	bool IsStarted();

	void CheckStartedAndRestoreIfDown();

	void ExecuteQueuedCommands();

	void SupplyLevelInit(char const * mapName);
	void SupplyLevelShutdown();

	void DrawingThread_SupplyCamData(CamData const & camData);

	void DrawingThread_PresentedUnleashCamDataOnFirstCall();
}

#endif
