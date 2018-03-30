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

	//After Render 벽
	collisionRect(player, BODY_DWBODY, room, RECT_WALL2, scale);


	CAMERAMANAGER->charMove(_isLeft, _isTop, _isRight, _isBottom, playerMove);
}



//렉트충돌 [원형]
void stageManager::collisionRect(player* player, BODYTYPE bodyType, stage1* room, RECTTYPE rectType, float scale)
{
	//벡터 사이즈
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
		 

		//충돌체크
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

							//무기 먹고 보유무기 버리기
							if (DATABASE->weapon.size() < 3)
							{
								room->removeVItem(RECT_WEAPON, i);
							}
							return;
						}
					break;
				}

				continue;
			}
			//==================================================================================

			//====================================== DOOR ======================================
			if (rectType == RECT_DOOR)
			{
				tagCollDoor tmpDoor;

				//문(열림/닫힘)
				if (KEYMANAGER->isOnceKeyDown('Z'))
				{
					if (room->getTileInfo(RECT_DOOR, i).actionValue == 0)
					{
						room->setTileDrAction(i, 1);
					}
					else room->setTileDrAction(i, 0);
				}

				//------------------------- 문 통과 -------------------------
				if (room->getTileInfo(RECT_DOOR, i).direction == DIR_LEFT)    //좌측문 
				{
					if (tmpRoom.left >= tmpPlayer.left)
					{
						//스테이지 변경
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				else if (room->getTileInfo(RECT_DOOR, i).direction == DIR_RIGHT)   //우측문 
				{
					if (tmpRoom.right <= tmpPlayer.right)
					{
						//스테이지 변경
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				else if (room->getTileInfo(RECT_DOOR, i).direction == DIR_TOP)     //상부문 
				{
					if (tmpRoom.bottom >= tmpPlayer.bottom)
					{
						//스테이지 변경
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				else if (room->getTileInfo(RECT_DOOR, i).direction == DIR_BOTTOM)  //하부문 
				{
					if (tmpRoom.top <= tmpPlayer.top)
					{
						//스테이지 변경
						stageChange(room->getTileInfo(RECT_DOOR, i).id);
						return;
					}
				}
				//-----------------------------------------------------------

	


				//충돌X
				if (room->getTileInfo(RECT_DOOR, i).actionValue == 1) continue;
			}
			//==================================================================================

			//예외처리
			if(rectType == RECT_ITEM || rectType == RECT_WEAPON) continue;


			//충돌(이동불가)
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

			//키 컨트롤 제한
			_collOn = true;
			break;
		}
	}
}

