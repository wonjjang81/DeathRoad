#include "stdafx.h"
#include "stageManager.h"

void stageManager::collisionPS(player* player, stage* room, int scale, bool playerMove)
{
	_collOn = false;

	_isLeft   = false;
	_isRight  = false;
	_isTop    = false;
	_isBottom = false;	


	CAMERAMANAGER->charMove(_isLeft, _isTop, _isRight, _isBottom, playerMove);

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

		tmpRoom.left   = room->getRect(rectType, i).left   * scale + _moveX + _moveChange.x;
		tmpRoom.top    = room->getRect(rectType, i).top    * scale + _moveY + _moveChange.y;
		tmpRoom.right  = room->getRect(rectType, i).right  * scale + _moveX + _moveChange.x;
		tmpRoom.bottom = room->getRect(rectType, i).bottom * scale + _moveY + _moveChange.y;

		if (tmpRoom.top == tmpRoom.bottom) continue;
		 

		//�浹üũ
		int cDirection = isCollisionReaction(tmpRoom, tmpPlayer);
		if (cDirection > 0)
		{
			if (rectType == RECT_ITEM || rectType == RECT_WEAPON)
			{
				switch (rectType)
				{
					case RECT_ITEM:
						if (room->getVectorSize(RECT_ITEM) == 0) continue;
			

						sprintf(_pItem->imgName, "%s", room->getTileInfo(RECT_ITEM, i).imgName);
						_pItem->tileType  = room->getTileInfo(RECT_ITEM, i).tileType;
						_pItem->attribute = room->getTileInfo(RECT_ITEM, i).attribute;
						_pItem->typeAtt   = room->getTileInfo(RECT_ITEM, i).typeAtt;
						_pItem->index     = room->getTileInfo(RECT_ITEM, i).index;

						DATABASE->inven.push_back(_pItem);

						room->removeVItem(RECT_ITEM, i);
						return;
					break;
					case RECT_WEAPON:
						if (room->getVectorSize(RECT_WEAPON) == 0) continue;
		

						sprintf(_pItem->imgName, "%s", room->getTileInfo(RECT_WEAPON, i).imgName);
						_pItem->tileType  = room->getTileInfo(RECT_WEAPON, i).tileType;
						_pItem->attribute = room->getTileInfo(RECT_WEAPON, i).attribute;
						_pItem->typeAtt   = room->getTileInfo(RECT_WEAPON, i).typeAtt;
						_pItem->index     = room->getTileInfo(RECT_WEAPON, i).index;

						DATABASE->inven.push_back(_pItem);

						room->removeVItem(RECT_WEAPON, i);
						return;
					break;
				}
			
				continue;
			}

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