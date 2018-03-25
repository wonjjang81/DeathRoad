#include "stdafx.h"
#include "stageManager.h"

void stageManager::collisionPS(player* player, stage* room, int scale)
{
	_collOn = false;

	_isLeft   = true;
	_isRight  = true;
	_isTop    = true;
	_isBottom = true;																																 

	CAMERAMANAGER->charMove(_isLeft, _isTop, _isRight, _isBottom);

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

	//After Render ��
	collisionRect(player, BODY_DWBODY, room, RECT_WALL2, scale);

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

		tmpRoom.left   = room->getRect(rectType, i).left   * scale + _moveX;
		tmpRoom.top    = room->getRect(rectType, i).top    * scale + _moveY;
		tmpRoom.right  = room->getRect(rectType, i).right  * scale + _moveX;
		tmpRoom.bottom = room->getRect(rectType, i).bottom * scale + _moveY;

		if (tmpRoom.top == tmpRoom.bottom) continue;
		

		//�浹üũ
		int cDirection = isCollisionReaction(tmpRoom, tmpPlayer);
		if (cDirection > 0)
		{
			if (rectType == RECT_ITEM || rectType == RECT_WEAPON) continue;

			switch (cDirection)
			{
				case C_TOP:
					_isBottom = false;
				break;
				case C_BOTTOM:
					_isTop = false;
				break;
				case C_LEFT:
					_isRight = false;
				break;
				case C_RIGHT:
					_isLeft = false;
				break;
			}

			//Ű ��Ʈ�� ����
			_collOn = true;
			break;
		}
	}
}