#include "Includes.h"

int main(int argc, char* argv[])
{
	ds::DynamicMatrix<int> mat(0, 2, 2);

	mat[0][0] = 1;
	mat.Insert(2, 0, 1);
	mat[1][0] = 3;
	mat.Insert(4, 1, 1);
	mat.Insert(5, 1, 2);
	mat.Insert(6, 2, 1);

	std::cout << mat[0][0] << std::endl;
	std::cout << mat.GetElementAt(0, 1) << std::endl;
	// std::cout << mat.GetElementAt(2, 1) << std::endl;
	// std::cout << mat.GetElementAt(1, 2) << std::endl;

	mat.Print();

	ds::DynamicMatrix<int> mat1(0);
	mat1 = mat;

	mat1.Print();

	ds::DynamicMatrix<int> mat2(std::move(mat1));
	mat1 = std::move(mat2);

	std::cout << "MAT 1\n";
	mat1.Print();
	std::cout << "MAT 2\n";
	mat2.Print();

	mat1.AddRows();
	mat1.Print();
	mat1.AddColumns();
	mat1.Print();
	mat1.AddCorner();
	mat1.Print();

	mat1[3][3] = 1;
	mat1.Print();

	mat1.SetInitial(1);
	mat1.Reinitialize();
	mat1.Print();

	return 0;
}