/*
#ifndef GENERIC_SKIP_LIST_H
#define GENERIC_SKIP_LIST_H
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <limits>
#include <string>
#define PROBABILITY_OF_ABOVE_LEVEL 2
using namespace std;

template<typename Key, typename Element>
class SkipList
{
protected:
	class QuadNode
	{
	private:
		Key _key;
		Element _elem;
	protected:
		QuadNode* up;
		QuadNode* down;
		QuadNode* prev;
		QuadNode* next;
		int level;
	public:
		QuadNode(Key k,	Element e = Element()) // constructor
			:_key(k), _elem(e)
		{
			up = down = prev = next = NULL;
			level = -1;
		}
		Key& key() { return _key; }
		Element& element() { return _elem; }
		void setKey(Key& k) { _key = k; }
		void setElement(Element& e) { _elem = e; }
		friend class Position;
	}; // end of QuadNode
public:
	class Position {
	protected:
		QuadNode* pQN;
	public:
		Position(QuadNode* pSLN) { pQN = pSLN; }
		Position() {}
		Key& key() { return pQN->key(); }
		Element& element() { return pQN->element(); }
		Position below() { return Position(pQN->down); }
		Position above() { return Position(pQN->up); }
		Position after() { return Position(pQN->next); }
		Position before() { return Position(pQN->prev); }
		void setBelow(Position p) { pQN->down = p.pQN; }
		void setAbove(Position p) { pQN->up = p.pQN; }
		void setAfter(Position p) { pQN->next = p.pQN; }
		void setBefore(Position p)
		{
			pQN->prev = p.pQN;
		}
		bool operator==(Position q)
		{
			return pQN == q.pQN;
		}
		bool operator!=(Position q)
		{
			return pQN != q.pQN;
		}
		Element& operator*() { return pQN->element(); }
		const Position operator=(const Position p)
		{
			this->pQN = p.pQN; return *this;
		}
		friend class SkipList;
	};
private:
	Position start; // skip list top
	Position end; // skip list bottom
	int height;
	int num_elements;
public:
	SkipList() // default constructor
	{
		height = 0;
		num_elements = 0;
		QuadNode* pQNode = new QuadNode(Key(" "), Element());
		start = Position(pQNode);
		pQNode = new QuadNode(Key("zzzzzzzz"), Element());
		end = Position(pQNode);
		start.setAfter(end);
		start.setBefore(Position(NULL));
		start.setAbove(Position(NULL));
		start.setBelow(Position(NULL));
		end.setBefore(start);
		end.setAfter(Position(NULL));
		end.setBelow(Position(NULL));
		end.setAbove(Position(NULL));
		//bottom = Position(NULL);
		srand(time(NULL));
	}
	Position SkipListSearch(Key& k)
	{
		Position pos = start;
		while (pos.below() != Position(NULL))
		{
			pos = pos.below();
			while (k >= ((pos.after()).key()))
			{
				pos = pos.after();
				if (pos.after() == (Position)NULL)
					break;
			} // inner while
		} // outer while
		return pos;
	}
	Position SkipListInsert(ostream& fout, Key k, Element e)
	{
		Position p, q, t;
		p = SkipListSearch(k);
		q = Position(NULL);
		int i = -1;
		do {
			i = i + 1;
			if (i >= height)
			{
				height = height + 1;
				t = start.after();
				start = insertAfterAbove(fout, Position(NULL), start, k, Element());
				insertAfterAbove(fout, start, t, "zzzzzzzzzzzz", Element());
			}
			q = insertAfterAbove(fout, p, q, k, e);
			while (p.above() == (Position)NULL)
			{
				p = p.before(); // scan backward
			}
			p = p.above(); // jump up to higher level
			//q = insertAfterAbove(p, q, k, e);
		} while (rand() % 2 == 0);
		// flip coin and continue if head occurs
		++num_elements;
		return q;
	}
	void SkipListNodeDelete(Position p)
	{
		Position pprev, pnext;
		if (p != Position(NULL))
		{
			pprev = p.before();
			pnext = p.after();
			if (pprev != Position(NULL))
				pprev.setAfter(pnext);
			if (pnext != Position(NULL))
				pnext.setBefore(pprev);
			delete p.pQN;
		}
	}
	void SkipListRemove(ostream& fout, Key k)
	{
		Position p, pprev, pnext, p00, px0;
		Position p0y, pxy, old_p;
		int h_max, h;
		p = SkipListSearch(k);
		if ((p.key() != k) || (p.key() == "A"))
		{
			fout << "Key (" << k << ") is not found";
			fout << "in SkipList !!" << endl;
			return;
		}
		while (p != Position(NULL))
		{
			old_p = p;
			p = p.above();
			SkipListNodeDelete(old_p);
		}
		fout << "deleted skip list node (Key: ";
		fout << k << ")" << endl;
		// compare the height of the skip list
		// and the highest tower level
		p00 = start;
		for (int i = height; i > 0; i--)
		{
			p00 = p00.below();
		}
		px0 = p00.after();
		pxy = start;
		h_max = 0;
		while (px0.key() != "zzzzzzzz")
		{
			pxy = px0;
			h = 0;
			while (pxy != Position(NULL))
			{
				++h;
				pxy = pxy.above();
			}
			if (h_max <h)
				h_max = h;
			px0 = px0.after();
		}
		if (h_max < height)
		{
			fout << "Current height is less than";
			fout << " the new h_max(" << h_max;
			fout << ") ==> need adjustment !!";
			fout << endl;
		}
		for (int i = 0; i < (height - h_max); i++)
		{
			p0y = start;
			pxy = start.after();
			start = start.below();
			SkipListNodeDelete(pxy);
			SkipListNodeDelete(p0y);
		}
		height = h_max;
	}
	void PrintSkipList(ostream& fout)
	{
		Position p, p00, px0, p0y, pxy, q, q0, qx;
		int level;
		fout << "Print Skip List Inside :";
		fout << "current height(" << height << ")";
		fout << endl;
		p00 = start;
		level = height;
		for (int i = height; i > 0; i--)
		{
			p00 = p00.below();
		}
		p0y = start;
		pxy = start;
		for (level = height; level >= 0; level--)
		{
			fout << "level" << setw(2);
			fout << level << " ";
			if (pxy.key() == "A")
				fout << "-oo";
			else
				fout << setw(5) << pxy.key();
			px0 = p00.after();
			for (pxy = p0y.after();; pxy = pxy.after())
			{
				while ((px0.key() != pxy.key()))
				{
					fout << " ------";
					px0 = px0.after();
				}
				
				if (pxy.key() == "zzzzzzzz")
				{
					break;
				}
				else {
					fout << " -" << setw(5);
					fout << pxy.key();
				}
				px0 = px0.after();
			}
			if (pxy.key() == "zzzzzzzz")
				fout << "\ +oo";
			else
				fout << setw(5) << pxy.key();
			fout << endl;
			p0y = p0y.below();
			pxy = p0y;
		}
		fout << endl;
	}
	Position insertAfterAbove(ostream& fout, Position p, Position q, const Key k, const Element e)
	{
		QuadNode* pNewNode = new QuadNode(k, e);
		Position n(pNewNode);
		n.setAbove(Position(NULL));
		n.setBelow(Position(NULL));
		n.setBefore(Position(NULL));
		n.setAfter(Position(NULL));
		if (p == Position(NULL))
		{
			if (q == Position(NULL))
			{
				fout << "Trying to insert at";
				fout << "(NULL, NULL)position";
				fout << endl;
				return Position(NULL);
			}
			else
			{
				q.setAbove(n);
				n.setBelow(q);
				n.setAbove(Position(NULL));
				n.setAfter(Position(NULL));
				return n;
			}
		}
		else
		{
			if (q == Position(NULL))
			{
				Position nx, ny;
				fout << "insert a node (" << n.key();
				fout << ") at level 0 " << endl;
				nx = p.after();
				p.setAfter(n);
				n.setBefore(p);
				n.setAfter(nx);
				nx.setBefore(n);
				n.setBelow(Position(NULL));
				n.setAbove(Position(NULL));
				return n;
			}
			else 
			{
				Position nx, ny;
				nx = p.after();
				n.setAfter(nx);
				if (nx != Position(NULL))
					nx.setBefore(n);
				p.setAfter(n);
				n.setBefore(p);
				ny = q.above();
				q.setAbove(n);
				n.setBelow(q);
				n.setAbove(ny);
				if (ny != Position(NULL))
					ny.setBelow(n);
			}
		} return n;
	}
};
#endif
*/


#ifndef GENERIC_SKIP_LIST_H
#define GENERIC_SKIP_LIST_H

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <limits>
#include <string>

#define PROBABILITY_OF_ABOVE_LEVEL 2
using namespace std;


template<typename K, typename V>
class SkipList {
public:
    class QuadNode;
    class Position;
public:
    SkipList();
    Position SkipListSearch(K& k);
    Position SkipListInsert(ostream& fout, K key, V ent);
    Position SkipListBegin()
    {
        Position bottom_start = getStart();

        while (bottom_start.below() != Position(NULL))
        {
            bottom_start = bottom_start.below();
        }
        if (this->size() != 0)
        {
            bottom_start = bottom_start.after();
        }
        return bottom_start;
    }
    Position SkipListEnd()
    {
        Position bottom_end = end;

        while (bottom_end.below() != Position(NULL))
        {
            bottom_end = bottom_end.below();
        }

        return bottom_end;
    }
    Position getStart() { return start; }
    Position getEnd() { return end; }
    void SkipListNodeDelete(Position p);
    void SkipListRemove(ostream& fout, K key);
    void PrintSkipList(ostream& fout);
    Position insertAfterAbove(ostream& fout, Position p, Position q, const K key, const V ent);
    int size() { return num_elements; }
private:
    Position start; // skip list top
    Position end; // skip list bottom
    int height;
    int num_elements;
};

template <typename K, typename V>
class SkipList<K, V>::QuadNode
{
private:
    K _key;
    V _entry;
protected:
    QuadNode* up;
    QuadNode* down;
    QuadNode* prev;
    QuadNode* next;
    int level;
public:
    QuadNode()
    {

    }
    QuadNode(K k, V e) :_key(k), _entry(e)
    {
        up = down = prev = next = NULL;
        level = -1;
    }
    K& key() { return _key; }
    V& entry() { return _entry; }
    void setKey(K& k) { _key = k; }
    void setElement(V& e) { _entry = e; }
    friend class Position;
    friend class SkipList<K, V>;
}; // end of QuadNode

template <typename K, typename V>
class SkipList<K, V>::Position
{
protected:
    QuadNode* pQN;
public:
    Position(QuadNode* pSLN) { pQN = pSLN; }
    Position() {}

    K& key() { return pQN->key(); }
    V& entry() { return pQN->entry(); }
    Position below() { return Position(pQN->down); }
    Position above() { return Position(pQN->up); }
    Position after() { return Position(pQN->next); }
    Position before() { return Position(pQN->prev); }
    void setBelow(Position p) { pQN->down = p.pQN; }
    void setAbove(Position p) { pQN->up = p.pQN; }
    void setAfter(Position p) { pQN->next = p.pQN; }
    void setBefore(Position p)
    {
        pQN->prev = p.pQN;
    }
    bool operator==(const Position& q) const
    {
        return pQN == q.pQN;
    }
    bool operator!=(const Position& q) const
    {
        return pQN != q.pQN;
    }
    V& operator*() { return pQN->entry(); }
    Position& operator=(const Position& p)
    {
        this->pQN = p.pQN;
        return *this;
    }
    friend class QuadNode;
    friend class SkipList<K, V>;
}; // end of class Position

template <typename K, typename V>
SkipList<K, V>::SkipList()
{
    height = 0;
    num_elements = 0;
    QuadNode* pQNode = new QuadNode(K(" "), V());//////////////////////////////////오류
    start = Position(pQNode);
    pQNode = new QuadNode(K("zzzzzz"), V());//////////////////////////////오류
    end = Position(pQNode);
    start.setAfter(end);
    start.setBefore(Position(NULL));
    start.setAbove(Position(NULL));
    start.setBelow(Position(NULL));
    end.setBefore(start);
    end.setAfter(Position(NULL));
    end.setBelow(Position(NULL));
    end.setAbove(Position(NULL));
    //bottom = Position(NULL);
    srand(time(NULL));
}

template <typename K, typename V>
typename SkipList<K, V>::Position
SkipList<K, V>::SkipListSearch(K& k)
{
    Position pos = start;
    while (pos.below() != Position(NULL))//제일 아랫단계까지 내려간다는 소리임
    {
        pos = pos.below();
        while (k >= ((pos.after()).key()))
        {
            pos = pos.after();
            if (pos.after() == (Position)NULL)
                break;//못찾았다는 소리
        } // inner while
    } // outer while
    return pos;
}

template <typename K, typename V>
typename SkipList<K, V>::Position
SkipList<K, V>::SkipListInsert(ostream& fout, K k, const V e)
{
    Position p, q, t;
    p = SkipListSearch(k);//제일 아랫단계 포지션을 잡아냄
    q = Position(NULL);
    int i = -1;
    do {
        i = i + 1;
        if (i >= height)
        {
            height = height + 1;
            t = start.after();
            //K k = MINUS_INF;
            start = insertAfterAbove(fout, Position(NULL), start, k, V());
            insertAfterAbove(fout, start, t, "zzzzzz", V());
        }//////////꼭대기인 경우 마이너스 무한대랑 플러스무한대 생성 시켜줌
        q = insertAfterAbove(fout, p, q, k, e);
        while (p.above() == (Position)NULL)
        {
            p = p.before(); // scan backward
        }
        p = p.above(); // jump up to higher level
        //q = insertAfterAbove(p, q, k, e);
    } while (rand() % 2 == 0);
    // flip coin and continue if head occurs
    ++num_elements;
    return q;
}

template <typename K, typename V>
void SkipList<K, V>::SkipListNodeDelete(Position p)///position p 자리를 지움
{
    Position pprev, pnext;
    if (p != Position(NULL))
    {
        pprev = p.before();
        pnext = p.after();
        if (pprev != Position(NULL))
            pprev.setAfter(pnext);
        if (pnext != Position(NULL))
            pnext.setBefore(pprev);
        delete p.pQN;
    }
}

template <typename K, typename V>
void SkipList<K, V>::SkipListRemove(ostream& fout, K k)
{
    Position p, pprev, pnext, p00, px0;
    Position p0y, pxy, old_p;
    int h_max, h;
    p = SkipListSearch(k);
    if ((p.key() != k) || (p.key() == "A"))//찾지 못했다는 소리
    {
        fout << "Key (" << k << ") is not found";
        fout << "in SkipList !!" << endl;
        return;
    }
    while (p != Position(NULL))//제일 아랫단계부터 윗단계로 올라가면서 p 자리를 지움(타워 삭제)
    {
        old_p = p;
        p = p.above();
        SkipListNodeDelete(old_p);
    }
    fout << "deleted skip list node (Key: ";
    fout << k << ")" << endl;
    // compare the height of the skip list
    // and the highest tower level
    // 밑의 과정은 불필요하게 높은 것을 지워버림
    p00 = start;
    for (int i = height; i > 0; i--)//p00 이과정을 통해 제일 아래단계의 -무한대 위치
    {
        p00 = p00.below();
    }
    px0 = p00.after();
    pxy = start;
    h_max = 0;
    while (px0.key() != "zzzzzzzz")
    {
        pxy = px0;
        h = 0;
        while (pxy != Position(NULL))
        {
            ++h;
            pxy = pxy.above();
        }
        if (h_max < h)
            h_max = h;
        px0 = px0.after();
    }
    if (h_max < height)
    {
        fout << "Current height is less than";
        fout << " the new h_max (" << h_max;
        fout << ") ==> need adjustment !!";
        fout << endl;
    }
    for (int i = 0; i < (height - h_max); i++)
    {
        p0y = start;
        pxy = start.after();
        start = start.below();
        SkipListNodeDelete(pxy);
        SkipListNodeDelete(p0y);
    }
    height = h_max;
}

template <typename K, typename V>
void SkipList<K, V>::PrintSkipList(ostream& fout)
{
    Position p, p00, px0, p0y, pxy, q, q0, qx;
    int level;
    fout << "Print Skip List Inside :";
    fout << "current height(" << height << ")";
    fout << endl;
    p00 = start;
    level = height;
    for (int i = height; i > 0; i--)
    {
        p00 = p00.below();
    }
    p0y = start;
    pxy = start;
    for (level = height; level >= 0; level--)
    {
        fout << "level" << setw(2);
        fout << level << " ";
        if (pxy.key() == " ")
            fout << "-oo";
        else
            fout << "   ";
        px0 = p00.after();
        for (pxy = p0y.after();; pxy = pxy.after())
        {
            while ((px0.key() != pxy.key()))
            {
                fout << " -------------";
                px0 = px0.after();
            }
            if (pxy.key() == "zzzzzz")
            {
                break;
            }
            else
            {
                fout << " -" << setw(12) << pxy.key();
            }
            px0 = px0.after();
        }
        if (pxy.key() == "zzzzzz")
            fout << " + oo";
        else
            fout << setw(12) << pxy.key();
        fout << endl;
        p0y = p0y.below();
        pxy = p0y;
    }
    fout << endl;
}

template <typename K, typename V>
typename SkipList<K, V>::Position
SkipList<K, V>::insertAfterAbove(ostream& fout, Position p, Position q, const K k, const V e)
{
    QuadNode* pNewNode = new QuadNode(k, e);
    Position n(pNewNode);
    n.setAbove(Position(NULL));
    n.setBelow(Position(NULL));
    n.setBefore(Position(NULL));
    n.setAfter(Position(NULL));
    if (p == Position(NULL))//마이너스 무한대 자리
    {
        if (q == Position(NULL))
        {
            fout << "Trying to insert at";
            fout << "(NULL, NULL) position";
            fout << endl;
            return Position(NULL);
        }
        else //
        {
            q.setAbove(n);
            n.setBelow(q);
            n.setAbove(Position(NULL));
            n.setAfter(Position(NULL));
            return n;
        }
    }
    else
    {
        if (q == Position(NULL))//제일 낮은 단계
        {
            Position nx, ny;
            fout << "insert a node (" << n.key();
            fout << ") at level 0 " << endl;
            nx = p.after();
            p.setAfter(n);
            n.setBefore(p);
            n.setAfter(nx);
            nx.setBefore(n);
            n.setBelow(Position(NULL));
            n.setAbove(Position(NULL));
            return n;
        }
        else
        {
            Position nx, ny;
            nx = p.after();
            n.setAfter(nx);
            if (nx != Position(NULL))
                nx.setBefore(n);
            p.setAfter(n);
            n.setBefore(p);
            ny = q.above();
            q.setAbove(n);
            n.setBelow(q);
            n.setAbove(ny);
            if (ny != Position(NULL))
                ny.setBelow(n);
        }
    }
    return n;
}


#endif