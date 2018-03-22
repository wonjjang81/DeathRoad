#include "stdafx.h"
#include "stageManager.h"

void stageManager::collisionPS(player* player, stage* room, int scale)
{
	_collOn = false;

	//����
	collisionRect(player, BODY_DWBODY, room, RECT_FURNITURE, scale);

	//������
	collisionRect(player, BODY_DWBODY, room, RECT_ITEM, scale);

	//����
	collisionRect(player, BODY_DWBODY, room, RECT_WEAPON, scale);

	//��
	collisionRect(player, BODY_DWBODY, room, RECT_WALL, scale);

	//��
	collisionRect(player, BODY_DWBODY, room, RECT_DOOR, scale);
}



//��Ʈ�浹 [����]
void stageManager::collisionRect(player* player, BODYTYPE bodyType, stage* room, RECTTYPE rectType, float scale)
{
	//���� ������
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

		//�浹üũ
		if (isCollisionReaction(tmpRoom, tmpPlayer))
		{
			_collOn = true;
			break;
		}
	}
}