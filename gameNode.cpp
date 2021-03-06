#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
	:_self(NULL), _parent(NULL),
	_prev(NULL), _next(NULL),
	_current(NULL), _childrenHead(NULL), 
	_childrenTail(NULL)
{
}


gameNode::~gameNode()
{

}

HRESULT gameNode::init(void)  
{
	//_hdc = GetDC(_hWnd);
	_managerInit = false;

	//이것을 젤 상위로
	setSelf(this);
	
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		SOUNDMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		INIDATA->init();
		DATABASE->init();
		D2DMANAGER->init();
		CAMERAMANAGER->init();
	}

	return S_OK;
}

void gameNode::release(void)  
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		INIDATA->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		DATABASE->release();
		DATABASE->releaseSingleton();
		D2DMANAGER->release();
		D2DMANAGER->releaseSingleton();
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();
	}

	_current = _childrenHead;

	gameNode* temp;

	while (_current != NULL)
	{
		temp = _current->getNext();
		_current->release();
		SAFE_DELETE(_current);
		_current = _childrenHead = temp;
	}

	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)	  
{
	SOUNDMANAGER->update();

	gameNode* current = _childrenHead;
	while (current != NULL)
	{
		current->update();
		current = current->getNext();
	}
}

void gameNode::render(void)
{
	gameNode* current = _childrenHead;
	while (current != NULL)
	{
		current->render();
		current = current->getNext();
	}
}

void gameNode::afterRender(void)
{
	gameNode* current = _childrenHead;
	while (current != NULL)
	{
		current->afterRender();
		current = current->getNext();
	}
}

void gameNode::addChild(gameNode* node)
{
	//연결된 씬이 없다면
	if (_childrenHead == NULL)
	{
		node->setParent(this);

		//맨 처음 등록 시킨 씬을 상위로 둔다
		setChildrenHead(node);

		setChildrenTail(NULL);
	}
	else
	{
		_current = _childrenHead;
		//다음 노드와 연결되어있지 않은 씬을 찾는다
		while (_current->getNext() != NULL)
		{
			_current = _current->getNext();
		}
		//상위씬을 이 씬으로 정하고
		node->setParent(this);
		//이전노드에는 찾은 마지막노드
		node->setPrev(_current);
		//맨 끝 노드 다음에 삽입해준다
		_current->setNext(node);
		//씬이 연결되었다면(꼬리) 포인터는 없다
		node->setNext(NULL);

		_childrenTail = node;
	}
}

//특정 차일드 지우기
void gameNode::removeChild(gameNode* node)
{
	int count = 0;
	_current = _childrenHead;

	gameNode* prev = NULL;

	while (_current != NULL)
	{
		if (_current == node)
		{
			if (count != 0)
			{
				prev->setNext(_current->getNext());
				if (_current->getNext() != NULL) _current->getNext()->setPrev(prev);
				else _childrenTail = _current;
			}
			else
			{
				_childrenHead = _current->getNext();
				if (_childrenHead != NULL) _childrenHead->setPrev(NULL);
			}

			_current->release();
			SAFE_DELETE(_current);
			break;
		}

		prev = _current;
		_current = _current->getNext();
		count++;
	}
}

//전부 지우기
void gameNode::removeAllChild()
{
	if (_childrenHead == NULL) return;

	int count = 0;
	_current = _childrenHead;

	gameNode* next = NULL;

	while (_current != NULL)
	{
		next = _current->getNext();

		if (next != NULL)
		{
			next->release();
			SAFE_DELETE(next);

			_current = _childrenHead;
			count++;
		}
		else
		{
			_current->release();
			SAFE_DELETE(_current);
			_childrenHead = NULL;
			return;
		}
	}
}

//현재씬을 제외한 나머지 차일드 제거
void gameNode::removeExceptChild(gameNode* node)
{
	int count = 0;
	_current = _childrenHead;

	gameNode* prev = NULL;

	while (_current != NULL)
	{
		if (_current != node)
		{
			if (count != 0)
			{
				prev->setNext(_current->getNext());
				if (_current->getNext() != NULL) _current->getNext()->setPrev(prev);
				else _childrenTail = _current;
			}
			else
			{
				_childrenHead = _current->getNext();
				if (_childrenHead != NULL) _childrenHead->setPrev(NULL);
			}

			_current->release();
			SAFE_DELETE(_current);
			break;
		}

		prev = _current;
		_current = _current->getNext();
		count++;
	}
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{	
	switch (iMessage)
	{
		case WM_PAINT:
		{
			D2DMANAGER->beginDraw();

			this->render();

			D2DMANAGER->endDraw();
		}
		break;
		case WM_TIMER:
			this->update();
		break;
		
		case WM_MOUSEMOVE:
		{

			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);

		}
		break;
	
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}