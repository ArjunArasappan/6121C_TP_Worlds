/*
Credit to VRC Team 315G for most of this code
*/

#include "main.h"

int autonNumber;
bool redAlliance;

static const char *btnm_map[] = {"F 5fl", "F 3fl P", "B 2F C", "B 2F P", "\n",
				 "",
				 "", "", "", ""};
static const char *auton_strings[] = {"F 5fl", "F 3fl P", "B 2F C", "B 2F P", "", "", "", ""};
static const char *alliance_map[] = {"Red", "Blue", ""};

static lv_res_t btnm_action(lv_obj_t *btnm, const char *txt)
{
	for (int i = 0; i < sizeof(auton_strings) / sizeof(auton_strings[0]); i++)
	{
		if (strcmp(auton_strings[i], txt) == 0)
		{
			autonNumber = i + 1;
			break;
		}
		lv_btnm_set_toggle(btnm, true, autonNumber);
	}

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t btnm_action_color(lv_obj_t *btnm, const char *txt)
{
	lv_btnm_set_toggle(btnm, true, 1);
	lv_btnm_set_toggle(btnm, true, 2);

	if (strcmp(txt, "Red") == 0)
	{
		redAlliance = true;
	}
	else if (strcmp(txt, "Blue") == 1)
	{
		redAlliance = false;
	}

	return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

void autonomousChooserPrintInfo(void *param)
{
	while (true)
	{
		printf("%d %d\n", autonNumber, redAlliance);
		pros::delay(20);
	}
}

void autonomousChooserInit()
{
	lv_theme_alien_init(40, NULL);

	lv_obj_t *title = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(title, "6121C Auton Selection");
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);

	lv_obj_t *btnm = lv_btnm_create(lv_scr_act(), NULL);
	lv_btnm_set_map(btnm, btnm_map);
	lv_btnm_set_action(btnm, btnm_action);
	lv_obj_set_size(btnm, LV_HOR_RES - 40, LV_VER_RES / 3);
	lv_obj_align(btnm, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

	lv_obj_t *allianceM = lv_btnm_create(lv_scr_act(), NULL);
	lv_btnm_set_map(allianceM, alliance_map);
	lv_btnm_set_action(allianceM, btnm_action_color);
	lv_obj_set_size(allianceM, LV_HOR_RES - 40, 50);
	lv_obj_align(allianceM, btnm, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
}

bool autonomousChooserGetRedAlliance()
{

	return redAlliance;
}

void autonomousChooserExecuteAuto()
{

	if (redAlliance)
	{
		switch (autonNumber)
		{
		case 1:
			redFront5Flags();
			break;
		case 2:
			redFront3FlagsPark();
			break;
		case 3:
			redBackSnipe(false);
			break;
		case 4:
			redBackSnipe(true);
			break;
		case 5:

			break;
		case 6:

			break;
		case 7:
			break;
		case 8:
			break;
		default:
			break;
		}
	}
	else if (!redAlliance)
	{
		switch (autonNumber)
		{
		case 1:
			blueFront5Flags();
			break;
		case 2:
			blueFront3FlagsPark();
			break;
		case 3:
			blueBackSnipe(false);
			break;
		case 4:
			blueBackSnipe(true);
			break;
		case 5:

			break;
		case 6:

			break;
		case 7:

			break;
		case 8:

			break;
		default:
			break;
		}
	}
}