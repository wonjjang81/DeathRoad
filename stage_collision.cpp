#include "stdafx.h"
#include "stageManager.h"

void stageManager::collisionPS(player* player, stage* room, int scale)
{
	_collOn = false;

	//가구
	collisionRect(player, BODY_DWBODY, room, RECT_FURNITURE, scale);

	//아이템
	collisionRect(player, BODY_DWBODY, room, RECT_ITEM, scale);

	//무기
	collisionRect(player, BODY_DWBODY, room, RECT_WEAPON, scale);

	//벽
	collisionRect(player, BODY_DWBODY, room, RECT_WALL, scale);

	//문
	collisionRect(player, BODY_DWBODY, room, RECT_DOOR, scale);
}



//렉트충돌 [원형]
void stageManager::collisionRect(player* player, BODYTYPE bodyType, stage* room, RECTTYPE rectType, float scale)
{
	//벡터 사이즈
	int vSize = room->getVectorSize(rectType);

	for (int i = 0; i < vSize; ++i)
	{
		RECT tmpRoom;
		RECT tmpPlayer = player->getRect(bodyType);

		tmpRoom.left   = room->getRect(rectType, i).left   * scale;
		tmpRoom.top    = room->getRect(rectType, i).top    * scale;
		tmpRoom.right  = room->getRect(rectType, i).right  * scale;
		tmpRoom.bottom = room->getRect(rectType, i).bottom * scale;

		if (tmpRoom.top == tmpRoom.bottom) continue;

		//충돌체크
		if (isCollisionReaction(tmpRoom, tmpPlayer))
		{
			_collOn = true;
			break;
		}
	}
}