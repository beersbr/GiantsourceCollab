#ifndef __SIZE_H__
#define __SIZE_H__

template <typename T>
class Size{
public:
	Size(T w, T h) : w(w), h(h)
	{
	}

	Size()
	{
		w = h = 0;
	}

public:
	T w;
	T h;
};

#endif