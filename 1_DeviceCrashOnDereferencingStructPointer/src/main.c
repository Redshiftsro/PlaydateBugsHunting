#include "pd_api.h"

static PlaydateAPI* pd;

static int update(void* userdata);
static void testCase();

typedef uint32_t MapDimension;

typedef struct
{
	MapDimension x;
	MapDimension y;
	MapDimension z;
}MapPosition;


#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* playdateAPI, PDSystemEvent event, uint32_t arg)
{
	pd = playdateAPI;
	(void)arg; // arg is currently only used for event = kEventKeyPressed

	if (event == kEventInit)
	{
		pd->system->setUpdateCallback(update, NULL);
		testCase();
	}

	return 0;
}

static int update(void* userdata)
{
	pd->graphics->clear(kColorWhite);
	pd->system->drawFPS(0, 0);

	return 1;
}

static void testCase()
{
	pd->system->logToConsole("Size of MapPosition %i", sizeof(MapPosition));

	size_t bufferSize = 100;
	size_t offset = 1;

	pd->system->logToConsole("offset is %i", offset);

	void* buffer = pd->system->realloc(NULL, bufferSize);
	memset(buffer, 0, bufferSize);

	MapPosition* mp = (char*)buffer + offset;
	mp->x = 1;
	mp->y = 2;
	mp->z = 3;

	// if MapDimension is defined as uint32_t
	// This will crash device if offset is 1,2,3
	// This will not crash device if offset is 0,4,8,12 ...
	MapPosition mpCopy = *mp;

	// if MapDimension is defined as uint16_t or uint8_t it works as intended.

	// In simulator everything always works.

	pd->system->logToConsole("mpCopy: %i %i %i", mpCopy.x, mpCopy.y, mpCopy.z);
}
