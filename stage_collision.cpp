#include "stdafx.h"
#include "stageManager.h"

void stageManager::collisionPS(player* player, stage1* room, int scale, bool playerMove)
{
	_collOn = false;

	_isLeft   = false;
	_isRight  = false;
	_isTop    = false;
	_isBottom = false;	


	CAMERAMANAGER->setCamMoveLeftOn(true);
	CAMERAMANAGER->setCamMoveRightOn(true);
	CAMERAMANAGER->setCamMoveTopOn(true);
	CAMERAMANAGER->setCamMoveBottomOn(true);

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


	CAMERAMANAGER->charMove(_isLeft, _isTop, _isRight, _isBottom, playerMove);
}



//��Ʈ�浹 [����]
void stageManager::collisionRect(player* player, BODYTYPE bodyType, stage1* room, RECTTYPE rectType, float scale)
{
	//���� ������
	int vSize = room->getVectorSize(rectType);


	for (int i = 0; i < vSize; ++i)
	{
		//����ó��
		if (i >= vSize) return;

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
			//====================================== ITEM ======================================
			if (rectType == RECT_ITEM || rectType == RECT_WEAPON)
			{
				tagInvenItem tmpItem;
				tagInvenWp   tmpWp;

				switch (rectType)
				{
					case RECT_ITEM:
						if (room->getVectorSize(RECT_ITEM) == 0) continue;

						sprintf(tmpItem.imgName, "%s", room->getTileInfo(RECT_ITEM, i).imgName);
						tmpItem.typeAtt = room->getTileInfo(RECT_ITEM, i).typeAtt;
						tmpItem.index = room->getTileInfo(RECT_ITEM, i).index;

						switch (tmpItem.typeAtt)
						{
							case TYPE_A_IT_DRUG:
								tmpItem.value = RND->getFromIntTo(1, 3);
							break;
							case TYPE_A_IT_FOOD:
								tmpItem.value = RND->getFromIntTo(1, 3);
							break;
							case TYPE_A_IT_OIL:
								tmpItem.value = RND->getFromIntTo(5, 50);
							break;
							case TYPE_A_IT_BULLET:
								tmpItem.value = RND->getFromIntTo(7, 30);
							break;
						}


						DATABASE->item.push_back(tmpItem);

						room->removeVItem(RECT_ITEM, i);
						return;
					break;
					case RECT_WEAPON:
						if (KEYMANAGER->isOnceKeyDown('Z'))
						{
							if (room->getVectorSize(RECT_WEAPON) == 0) continue;
							if (DATABASE->weapon.size() >= 3) continue;

							sprintf(tmpWp.imgName, "%s", room->getTileInfo(RECT_WEAPON, i).imgName);
							tmpWp.typeAtt = room->getTileInfo(RECT_WEAPON, i).typeAtt;
							tmpWp.index = room->getTileInfo(RECT_WEAPON, i).index;
							tmpWp.frameX = room->getTileInfo(RECT_WEAPON, i).frameX;
							tmpWp.frameY = room->getTileInfo(RECT_WEAPON, i).frameY;
							//tmpItem.value = 0;

							DATABASE->weapon.push_back(tmpWp);

							//���� �԰� �������� ������
							if (DATABASE->weapon.size() < 3)
							{
								room->removeVItem(RECT_WEAPON, i);
							}

							//���Ⱑ ���� ������ ���

							return;
						}
					break;
				}

				continue;
			}

			//�浹X
			if (rectType == RECT_ITEM || rectType == RECT_WEAPON) continue;
			//==================================================================================

			//====================================== DOOR ======================================
			if (rectType == RECT_DOOR)
			{
				tagCollDoor tmpDoor;

				//��(����/����)
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					if (room->getTileInfo(RECT_DOOR, i).actionValue == 0)
					{
						room->setTileDrAction(i, 1);
					}
					else room->setTileDrAction(i, 0);
				}

				//------------------------- �� ��� -------------------------
				if (room->getTileInfo(RECT_DOOR, i).direction == DIR_LEFT)    //������ 
				{
					if (tmpRoom.left >= tmpPlayer.left)
					{
						//�������� ����
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				else if (room->getTileInfo(RECT_DOOR, i).direction == DIR_RIGHT)   //������ 
				{
					if (tmpRoom.right <= tmpPlayer.right)
					{
						//�������� ����
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				else if (room->getTileInfo(RECT_DOOR, i).direction == DIR_TOP)     //��ι� 
				{
					if (tmpRoom.bottom >= tmpPlayer.bottom)
					{
						//�������� ����
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				else if (room->getTileInfo(RECT_DOOR, i).direction == DIR_BOTTOM)  //�Ϻι� 
				{
					if (tmpRoom.top <= tmpPlayer.top)
					{
						//�������� ����
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				//-----------------------------------------------------------


				//�浹X
				if (room->getTileInfo(RECT_DOOR, i).actionValue == 1) continue;
			}
			//==================================================================================

			//=================================== FURNITURE ====================================
			if (rectType == RECT_FURNITURE)
			{			
				//�������
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					if (_vHaveFt.size() == 0)
					{
						_vHaveFt.push_back(room->getTileInfo(RECT_FURNITURE, i));
						room->removeVItem(RECT_FURNITURE, i);
					}
					else
					{
						room->setVTilePush(RECT_FURNITURE, _vHaveFt[0]);     //�÷��̾� �������� -> �������Ϳ� ���
						room->setVTileCpoy(RECT_FURNITURE, i, _vHaveFt[0]);  //��ġ���� ����
						_vHaveFt.erase(_vHaveFt.begin());                    //�÷��̾� �������� �����
						_vHaveFt.clear();

						_vHaveFt.push_back(room->getTileInfo(RECT_FURNITURE, i));  //�÷��̾� �������Ϳ� ���
						room->removeVItem(RECT_FURNITURE, i);                      //�������Ϳ��� �����
					}
			
					return;
				}
				else
				{
					float moveValue = 2;

					//����ó��: ���� �ε�ġ��


					switch (cDirection)
					{
						case C_TOP:
							room->setTileFtMoveRc(i, 0.0f, moveValue);
							room->setTileFtMoveXY(i, 0.0f, moveValue);
						break;
						case C_BOTTOM:
							room->setTileFtMoveXY(i, 0.0f, -moveValue);
							room->setTileFtMoveRc(i, 0.0f, -moveValue);
						break;
						case C_LEFT:
							room->setTileFtMoveXY(i, moveValue, 0.0f);
							room->setTileFtMoveRc(i, moveValue, 0.0f);
						break;
						case C_RIGHT:
							room->setTileFtMoveRc(i, -moveValue, 0.0f);
							room->setTileFtMoveXY(i, -moveValue, 0.0f);
						break;
					}
				}

				continue;
			}
			else
			{
				room->setTileFtMoveXY(i, 0, 0);
				room->setTileFtMoveRc(i, 0, 0);
			}
			//==================================================================================


			//�浹(�̵��Ұ�)
			switch (cDirection)
			{
				case C_TOP:
					_isBottom = false;
					CAMERAMANAGER->setCamMoveBottomOn(false);
				break;
				case C_BOTTOM:
					_isTop = false;
					CAMERAMANAGER->setCamMoveTopOn(false);
				break;
				case C_LEFT:
					_isRight = false;
					CAMERAMANAGER->setCamMoveRightOn(false);
				break;
				case C_RIGHT:
					_isLeft = false;
					CAMERAMANAGER->setCamMoveLeftOn(false);
				break;
			}

			//Ű ��Ʈ�� ����
			_collOn = true;
			break;
		}
	}
}

