#include "stdafx.h"
#include "collision.h"

namespace HEPTA_UTIL
{
	int isCollisionReaction(const RECT& rcHold, RECT& rcMove)
	{
		//��Ʈ���� �浹������ �ȿ� �����Ǵ� ��Ʈ 
		RECT rcInter;

		//�浹���� �ʾҴٸ� ������ ���ʿ��ϴ�!
		if (!IntersectRect(&rcInter, &rcHold, &rcMove)) return 0;

		int interSectorW = rcInter.right - rcInter.left;
		int interSectorH = rcInter.bottom - rcInter.top;
		//�������� �ε����ٸ�~~~
		if (interSectorW > interSectorH)
		{
			//������ �ھ�����
			if (rcInter.top == rcHold.top)
			{
				OffsetRect(&rcMove, 0, -interSectorH);
				return 1;
			}
			else if (rcInter.bottom == rcHold.bottom)//�Ʒ����� �ε����ٸ�
			{
				OffsetRect(&rcMove, 0, interSectorH);
				return 2;
			}
		}
		else
		{
			//�����ʿ��� ���� ������
			if (rcInter.left == rcHold.left)
			{
				OffsetRect(&rcMove, -interSectorW, 0);
				return 3;
			}
			else if (rcInter.right == rcHold.right)
			{
				OffsetRect(&rcMove, interSectorW, 0);
				return 4;
			}
		}
	}

}

