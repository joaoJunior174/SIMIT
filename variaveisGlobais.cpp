#include <cstdlib>
#include "glm/vec2.hpp"
#include <vector>
#include <list>
#include "glm/vec3.hpp"
#include <fstream>


using namespace std;
using glm::vec3;
//Os define da vida
bool CUBO =  false;
bool ESFERA =  false;
bool PIRAMIDE =  false;
bool selecionarSala = false;
bool selecionarBounding = false;
bool selecionarCena = false;
GLfloat indiceEixoX=0;
GLfloat indiceEixoY=0;
vector<vec3> pontoCubo(8);
vector<vector<vec3> > pontoEsfera;
vector<vec3> pontoPiramide;
vector<vec3> pontoCameraEixoX;
vector<vec3> pontoCameraEixoY;
GLfloat angle=60, fAspect;
GLfloat r=0;
GLfloat l=0;
GLfloat top=0;
GLfloat bottom=0;
GLfloat near, far;
GLint pg=0;
string nomeImagem;
int contImagem=0;
GLint widthFrame = 640;
GLint heightFrame = 480;
bool toZero = false;
vector< unsigned int > vertexIndices, uvIndices, normalIndices;
vector<vec3> vertices;
vector<vec3> normals;
vector<vec3> rgb;
vector<GLuint> ind;
vector<int> verticesDeFronteira;
int contadorDeArquivosText=0;
vector<int> pontosDefronteiraSalvo;
int cont_aux = 0;
GLfloat motion=0;
bool press=false;

// angle of rotation for the camera direction
float anglee=0.0,angley=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f,ly=0.0f;

int BoxCenter;

class Grafo{

public:
  vector<list<int> > lista;

  Grafo(){}

  void preencherGrafo(int size){

      for(int i=0;i<=size;i++){

          list<int> v;
          lista.push_back(v);
      }

  }

};

class StructureToProjection{

public:
  vec3 points;
  int ind;

};

class StructureSiftPoints{

public:
  vector<vec3> pointsWithNoFilter;
  vector<StructureToProjection> pointsFilteredTo3D;


};
class StructureBoundingBox{

  public:
    int left=0;
    int top=0;
    int width=0;
    int height=0;


};

StructureSiftPoints sPoints;
StructureBoundingBox bBox;
vector<StructureToProjection> borderPoints;
vector<StructureToProjection> projection;
Grafo grafo;
