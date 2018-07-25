#include "Includes.h"

void error(const char *error)
{
    printf("[Title-deleter:Error] %s", error);
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
}

int main()
{
    gfxInitDefault();
    nsInitialize();
    fsInitialize();
    consoleInit(NULL);
	printf("%s%s%s", CONSOLE_RED, "Please be aware by using this program you risk a brick", CONSOLE_RESET);
    printf("\n");
    printf("[Title-deleter:Info] Reading title file (sdmc:/switch/title-deleter.txt)\n");
    printf("[Title-deleter:Info] Press A to delete the titles from title-deleter.txt");
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
        hidScanInput();
        int k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A)
        {
			ifstream ifs("sdmc:/switch/title-deleter.txt");
			if(ifs.good())
			{
				string buf;
				while(getline(ifs, buf))
				{
					buf.pop_back();
					u64 id = strtoull(buf.c_str(), NULL, 16);
					Result res = nsDeleteApplicationCompletely(id);
					if(R_SUCCEEDED(res))
					{
						printf("deleted %s!\n", id);
					}
					else error("Failure deleting SystemUpdater %s.\n", id);
				}
			}
			ifs.close();
			printf("%s%s%s", CONSOLE_GREEN, "Complete, feel free to exit to the home menu.", CONSOLE_RESET);
        }
    }
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }
    nsExit();
    fsExit();
    gfxExit();
}
