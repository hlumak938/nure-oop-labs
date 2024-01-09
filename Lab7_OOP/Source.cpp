#include <iostream>
#include <ctime>
using namespace std;
template <class T>
class Array2D
{
public:
	class Array1D
	{
	private:
		int dim2;
		T* Array1;
	public:
		friend class Array2D;
		Array1D() :Array1(NULL), dim2(0) {}
		T& operator[](int index);
		const T& operator[] (int index) const;
	}; //class Array1D 
private:
	int dim1;
	Array1D* Array2;
public:
	Array2D() :dim1(0), Array2(NULL) {};
	Array2D(int d1, int d2);
	virtual ~Array2D();
	Array1D& operator[] (int index)
	{
		return Array2[index];
	}
	const Array1D& operator[] (int index) const
	{
		return Array2[index];
	}
};
int main()
{
	srand(time(0));
	int n(4), m(4);
	Array2D<int> array2D(n, m);
	for (int i = 0; i < n; cout << endl, ++i)
		for (int j = 0; j < m; ++j)
		{
			array2D[i][j] = rand() % 11;
			cout << array2D[i][j] << '\t';
		}
	cout << endl;
	int product = 1;
	for (int i = 0; i < n - 1; ++i)
		for (int j = i + 1; j < m; ++j)
			if (array2D[i][j] % 2 == 0)
				product *= array2D[i][j];
	cout << "Product of elements above the main diagonal = " << product << endl;
	return 0;
}

template <class T>
T& Array2D<T>::Array1D::operator[](int index)
{
	return Array1[index];
}
template <class T>
const T& Array2D<T>::Array1D::operator[](int index)const
{
	return Array1[index];
}
template <class T>
Array2D<T>::Array2D(int d1, int d2)
{
	dim1 = d1;
	Array2 = new Array1D[dim1];
	for (int i(0); i < d1; ++i)
	{
		Array2[i].dim2 = d2;
		Array2[i].Array1 = new T[d2];
	}
}
template <class T>
Array2D<T>::~Array2D()
{
	for (int i(0); i < dim1; ++i)
	{
		delete[]Array2[i].Array1;
	}
	delete[] Array2;
}
