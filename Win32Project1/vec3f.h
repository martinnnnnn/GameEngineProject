#pragma once



#include "Utils.h"



using namespace GameEngineProject::Utils;

namespace GameEngineProject
{

	namespace Vector
	{
		class vec3f;
		void calcNormale(vec3f & vec1, vec3f & vec2, vec3f & normale);
		
		inline bool isNaN(float value)
		{
			return (value != value);
		}

		inline float nanToZero(float value)
		{
			if (value != value)
				return 0;
			return value;
		}

		class vec3f
		{
		public:
			float x;
			float y;
			float z;

			vec3f() : x(0), y(0), z(0)
			{
			}

			vec3f(float X, float Y, float Z)
			{
				x = X;
				y = Y;
				z = Z;
			}

			void Reset()
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}

			std::string toStr()
			{
				std::string ret;
				ret += "X:";
				ret += ToString(x);
				ret += " Y:";
				ret += ToString(y);
				ret += " Z:";
				ret += ToString(y);
				return ret;
			}

			vec3f & operator= (const vec3f & vertex)
			{
				x = vertex.x;
				y = vertex.y;
				z = vertex.z;

				return *this;
			}

			vec3f & operator*= (float scalaire)
			{
				x *= scalaire;
				y *= scalaire;
				z *= scalaire;

				return *this;
			}

			vec3f & operator/= (float scalaire)
			{
				x /= scalaire;
				y /= scalaire;
				z /= scalaire;

				return *this;
			}

			vec3f operator * (float scalaire)
			{
				vec3f temp(
					x * scalaire,
					y * scalaire,
					z * scalaire);
				return temp;
			}

			vec3f operator / (float scalaire)
			{
				vec3f temp(
					x / scalaire,
					y / scalaire,
					z / scalaire);
				return temp;
			}

			vec3f operator + (const vec3f & vertex)
			{
				vec3f temp(
					x + vertex.x,
					y + vertex.y,
					z + vertex.z);
				return temp;
			}

			vec3f operator - (const vec3f & vertex)
			{
				vec3f temp(
					x - vertex.x,
					y - vertex.y,
					z - vertex.z);
				return temp;
			}

			vec3f & operator+= (const vec3f & vertex)
			{
				x += vertex.x;
				y += vertex.y;
				z += vertex.z;

				return *this;
			}

			vec3f & operator-= (const vec3f & vertex)
			{
				x -= vertex.x;
				y -= vertex.y;
				z -= vertex.z;

				return *this;
			}

			bool operator== (const vec3f & vertex)
			{
				if (x == vertex.x && y == vertex.y && z == vertex.z)
					return true;
				return false;
			}


			float getSize(void)
			{
				return sqrt(x*x + y*y + z*z);
			}

			float getMagnitude(void)
			{
				return x*x + y*y + z*z;
			}

			vec3f & normalize(void)
			{
				float longueur = getSize();
				if (longueur)
				{
					x /= longueur;
					y /= longueur;
					z /= longueur;
				}
				return *this;
			}

			void createTab(float * tab)
			{
				tab[0] = x;
				tab[1] = y;
				tab[2] = z;
			}

			void initFromTab(float * tab)
			{
				x = tab[0];
				y = tab[1];
				z = tab[2];
			}

			///Le produit scalaire (dot product)
			float scalProd(const vec3f & vertex)
			{
				return vertex.x*x + vertex.y*y + vertex.z*z;
			}

			///Le produit vectoriel
			vec3f vecProd(const vec3f & vertex)
			{
				vec3f produit(
					y*vertex.z - z*vertex.y,
					z*vertex.x - x*vertex.z,
					x*vertex.y - y*vertex.x);
				return produit;
			}

			///L'angle que fait ce vecteur sur le plan dont Y est la normale
			float angleY(vec3f & vertex)
			{
				vec3f moi(x, 0, z);
				moi.normalize();
				vec3f lui(vertex.x, 0, vertex.z);
				lui.normalize();

				float cosAng = moi.x*lui.x + moi.z*lui.z;
				vec3f normale;
				calcNormale(vertex, moi, normale);

				float res = acos(cosAng);
				if (isNaN(res))
				{
					if (cosAng > 0.5f)
						res = 0.0f;
					else
						res = 3.14159f;
				}

				if (normale.y >= 0)
					return -res;

				return res;
			}

			///L'angle que fait ce vecteur sur le plan dont Z est la normale
			float angleZ(vec3f & vertex)
			{
				vec3f moi(x, y, 0);
				moi.normalize();
				vec3f lui(vertex.x, vertex.y, 0);
				lui.normalize();

				float cosAng = moi.x*lui.x + moi.y*lui.y;
				vec3f normale;
				calcNormale(vertex, moi, normale);

				float res = acos(cosAng);
				if (isNaN(res))
				{
					if (cosAng > 0.5f)
						res = 0.0f;
					else
						res = 3.14159f;
				}

				if (normale.z >= 0)
					return -res;

				return res;
			}

			vec3f & rotate(vec3f & axe, float angle)
			{
				float matrice[4][4];

				if (angle < 0.001 && angle > -0.001)
					angle = 0;

				//Calculs fait une fois pour eco
				float cosi = cos(angle);
				float sinu = sin(angle);
				float x = axe.x;
				float y = axe.y;
				float z = axe.z;
				float x2 = axe.x*axe.x;
				float y2 = axe.y*axe.y;
				float z2 = axe.z*axe.z;

				//Creation de la matrice de rot

				//Ligne 1
				matrice[0][0] = x2 + (cosi*(1 - x2));
				matrice[1][0] = (x*y*(1 - cosi)) - (z*sinu);
				matrice[2][0] = (x*z*(1 - cosi)) + (y*sinu);
				matrice[3][0] = 0;

				//Ligne 2
				matrice[0][1] = (x*y*(1 - cosi)) + (z*sinu);
				matrice[1][1] = y2 + (cosi*(1 - y2));
				matrice[2][1] = (y*z*(1 - cosi)) - (x*sinu);
				matrice[3][1] = 0;

				//Ligne 3
				matrice[0][2] = (x*z*(1 - cosi)) - (y*sinu);
				matrice[1][2] = (y*z*(1 - cosi)) + (x*sinu);
				matrice[2][2] = z2 + (cosi*(1 - z2));
				matrice[3][2] = 0;

				//Ligne 4
				matrice[0][3] = 0;
				matrice[1][3] = 0;
				matrice[2][3] = 0;
				matrice[3][3] = 1;

				//Produit du vecteur par la matrice
				vec3f transforme;
				transforme.x = x * matrice[0][0] + y * matrice[1][0] + z * matrice[2][0];
				transforme.y = x * matrice[0][1] + y * matrice[1][1] + z * matrice[2][1];
				transforme.z = x * matrice[0][2] + y * matrice[1][2] + z * matrice[2][2];

				*this = transforme;

				//Affectation
				return *this;
			}

			void toSphericalCoordinates(float * dist, float * theta, float * phi)
			{
				*dist = this->getSize();
				*phi = atan2(y, x);
				*theta = atan2(sqrt(x*x + y*y), z);
			}





		};


	}



}







