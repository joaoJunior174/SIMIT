#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/gtx/io.hpp"
#include "desenharBoundingBoxes.cpp"


struct Face{

   int iv1;
   int iv2;
   int iv3;
   int in1;
   int in2;
   int in3;


};
vector<Face> faces;

using namespace std;
using glm::vec3;


GLfloat maxx=-100;
GLfloat maxy=-100;
GLfloat maxz=-100;
GLfloat minx=100;
GLfloat miny=100;
GLfloat minz=100;

bool loadObjFromArchive(char * path, char tipo){

	vector<vec3> temp_vertices;
	vector<vec3> temp_faces;
	vector<vec3> temp_normals;
	vector<vec3> temp_rgb;

	FILE * file = fopen(path, "r");
        FILE * fileCount = fopen(path, "r");

        if( file == NULL){

             printf("Not possible to read the file, please verify if it's an obj type");
             return false;

	}



	if(tipo == 'h'){//hololens


        }
  else if(tipo == 'b'){//bundlefusion

       int contVerticeInt=0;
       int ponteiroArquivo;

       while(1){

         char contVerticeChar[500];
         ponteiroArquivo = fscanf(fileCount,"%s",contVerticeChar);

        if(ponteiroArquivo == EOF){

            break;

        }

        if(contVerticeChar[0] == 'v' && contVerticeChar[1] != 'n'){

            contVerticeInt++;

          }

      }

      cout<<"Total de vertices: "<<contVerticeInt<<endl;
      grafo.preencherGrafo(contVerticeInt);

	     int cont = 0;
       while(1){

          char lineHeader[500];
          int res = fscanf (file,"%s",lineHeader);

          if (res == EOF){
              break;
          }
		      ind.push_back(cont);
		      cont++;
          if(lineHeader[0] == 'v' && lineHeader[1] == 'n'){

              vec3 vert;
              fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
		          normals.push_back(vert);

           }

           else if(lineHeader[0] == 'v'){
               vec3 vert;
               vec3 color;
               fscanf(file, "%f %f %f %f %f %f\n", &vert.x, &vert.y, &vert.z, &color.x,&color.y,&color.z);

               if(minx > vert.x){

                    minx=vert.x;

                }
                if(miny > vert.y){

                    miny=vert.y;

                }
                if(minz > vert.z){

                    minz=vert.z;

                }
                if(maxx < vert.x){

                    maxx=vert.x;

                }
                if(maxy < vert.y){

                    maxy=vert.y;

                }
                if(maxz < vert.z){

                    maxz=vert.z;

                }

		            vertices.push_back(vert);
                rgb.push_back(color);


                 }else if(lineHeader[0] == 'f'){

                     int v1=0,n1=0,v2=0,n2=0,v3=0,n3=0;
                     fscanf(file, "%d//%d %d//%d %d//%d\n", &v1, &n1, &v2, &n2, &v3,&n3);
                     Face f;
                     f.iv1 = v1;
                     f.iv2 = v2;
                     f.iv3 = v3;
                     f.in1 = n1;
                     f.in2 = n2;
                     f.in3 = n3;
                     faces.push_back(f);
                     grafo.lista[f.iv1].push_back(f.iv2);
                     grafo.lista[f.iv1].push_back(f.iv3);
                     grafo.lista[f.iv2].push_back(f.iv1);
                     grafo.lista[f.iv3].push_back(f.iv1);
                     grafo.lista[f.iv2].push_back(f.iv3);
                     grafo.lista[f.iv3].push_back(f.iv2);

		 }

             }


            /* for(int h=1;h<grafo.lista.size();h++){

                cout<<"Vertice: "<<h<<" Vizinhos: "<<grafo.lista[h].size()<<endl;

             }*/


        }

        return true;
}
void desenharSala(){
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glColor3f(0.0f, 0.0f, 1.0f);

        glBegin(GL_LINES);

    glLineWidth(2.0f);
    for(int i=-300;i<300;i=i+5){

        glColor3f(0.55,  0.55, 0.55);
        //desenhar na horizontal
	      glVertex3f(i,-5,300);
        glVertex3f(i,-5,-300);
          glColor3f(0.55,  0.55, 0.55 );
        //desenhar na vertical
        glVertex3f(300,-5,i);
        glVertex3f(-300,-5,i);
    }

    glEnd();

    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
       glPointSize(8);

       if(!pontosDefronteiraSalvo.empty()){

    //glBegin(GL_LINE_STRIP);
    for(int i=0;i<pontosDefronteiraSalvo.size();i++){

           glBegin(GL_POINTS);

           glColor3f(1.0f,0.0f,0.0f);
           glVertex3f(vertices[pontosDefronteiraSalvo[i]].x,vertices[pontosDefronteiraSalvo[i]].y,vertices[pontosDefronteiraSalvo[i]].z);
           glColor3f(0.0f,1.0f,0.0f);

           glEnd();
       }
    }


//  }
  /* if(!verticesDeFronteira.empty()){
     //glBegin(GL_LINE_STRIP);
     for(int i=0;i<verticesDeFronteira.size();i++){

        //  cout<<"Pontos de fronteira: "<<vertices[verticesDeFronteira[i]]<<endl;

         glBegin(GL_POINTS);

         glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(vertices[verticesDeFronteira[i]].x,vertices[verticesDeFronteira[i]].y,vertices[verticesDeFronteira[i]].z);
        //glVertex3f(vertices[sPoints.pointsFilteredTo3D[i].ind].x,vertices[sPoints.pointsFilteredTo3D[i].ind].y,vertices[sPoints.pointsFilteredTo3D[i].ind].z);
        glEnd();
     }

    // glEnd();

  }*/


        //cout<<"Quantidades de vertice: "<<vertices.size()<<endl;
        //cout<<"Quantidades de normals: "<<normals.size()<<endl;
        //cout<<"Quantidades de vertices com cores: "<<rgb.size()<<endl;
        //cout<<"Quantidades de faces: "<<faces.size()<<endl;

	//modo triangulo
  glBegin(GL_POINTS);
  glColor3f(0.0f,0.0f,1.0f);
  glVertex3f(vertices[BoxCenter].x,vertices[BoxCenter].y,vertices[BoxCenter].z);
  glEnd();

  glBegin(GL_TRIANGLES);

	//cout <<" desenha invertido"<<endl;
	//for(int i=0;i<faces.size();i++){

	for(int i=faces.size()-1; i>=0;i--){
	       glColor3f(rgb[faces[i].iv1].x,rgb[faces[i].iv1].y,rgb[faces[i].iv1].z);
	       glVertex3f(vertices[faces[i].iv1].x,vertices[faces[i].iv1].y,vertices[faces[i].iv1].z);
	       glColor3f(rgb[faces[i].iv2].x,rgb[faces[i].iv2].y,rgb[faces[i].iv2].z);
         glVertex3f(vertices[faces[i].iv2].x,vertices[faces[i].iv2].y,vertices[faces[i].iv2].z);
         glColor3f(rgb[faces[i].iv3].x,rgb[faces[i].iv3].y,rgb[faces[i].iv3].z);
	       glVertex3f(vertices[faces[i].iv3].x,vertices[faces[i].iv3].y,vertices[faces[i].iv3].z);
  }

  glEnd();

  if(CUBO){

      desenharCubo();

  }else if(ESFERA){

      desenharEsfera();

  }else if(PIRAMIDE){


  }

	glutSwapBuffers();


}
