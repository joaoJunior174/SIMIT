//#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/gtx/io.hpp"
#include "variaveisGlobais.cpp"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <GL/glx.h>
#include "pngwriter.cc"
#include "leituraObj.cpp"
#include "rotacaoMalha.cpp"
#include "matrizProjecao.cpp"
#include "gerarMenu.cpp"
#define GL_GLEXT_PROTOTYPES
#include "Camera.cpp"
#include "calcularProjecao.cpp"
#include "lerInfoB.cpp"
#include "lerPontoSift.cpp"
#include "calcularPontosDeFronteira.cpp"
#include "propostaExperimental.cpp"

//#include <GL/glext.h>
#include <algorithm>

using namespace std;
using glm::vec3;


void saveScreenToImage();
void Displays();
void Reshape (int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();
void Grid();

Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
bool g_fps_mode = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;

// Movement settings
const float g_translation_speed = 0.05;
const float g_rotation_speed = M_PI/180*0.2;

//Camera camera = Camera(posx,posy,0,0.5,0.5,0.1,0.1,500,600);
// Inicializa parâmetros de rendering
void Inicializa(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	angle = 30;
  win=150.0f;

}/*
// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
        //cout<<"aquiii: "<<fAspect<<endl;
	gluPerspective(angle, fAspect, 1.0f, 100);
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

  //camera.translation();
	// Especifica posição do observador e do alvo
	gluLookAt(posx, posy, posz, lookx, looky, lookz, rotx, roty, rotz);
	//gluLookAt(	posx, posy, posz,posx+lx, looky+ly,  posz+lz,rotx, roty, rotz);
        //gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
				//lookx=0;looky=0;lookz=0;

				//cout<<"aqui juh: "<<camera.getSightX()<<" "<<camera.getSightY()<<" "<<camera.getSightZ()<<endl;
				//gluLookAt(camera.getX(), camera.getY(), camera.getZ(), camera.getSightX(), camera.getSightY(), camera.getSightZ(), 0, 1, 0);
}*/
/*
// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
// Para previnir uma divisão por zero
if (h == 0) h = 1;
	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;
	EspecificaParametrosVisualizacao();
}*/

void tecladoSeta(int key,int x, int y){
   //camera.setKeyboard(key, true);

   float fraction = 0.1f;

     if(selecionarSala){

		     if(key== GLUT_KEY_LEFT){

		        //cout<<"Entrei aqui sim cara!"<<endl;
		        rotacionarMalha3DY(-15);

		     }else if(key == GLUT_KEY_RIGHT){

		        rotacionarMalha3DY(15);

		     }else if(key == GLUT_KEY_DOWN){

		        rotacionarMalha3DX(15);

		     }else if(key == GLUT_KEY_UP){

		        rotacionarMalha3DX(-15);


		     }
		}else if(selecionarBounding && CUBO){

			if(key== GLUT_KEY_LEFT){

				 rotacionarMalha3DYCubo(-15);
        //transladarEixoXCubo(1);
			}else if(key == GLUT_KEY_RIGHT){

         rotacionarMalha3DYCubo(15);

			}else if(key == GLUT_KEY_DOWN){

         rotacionarMalha3DXCubo(15);

			}else if(key == GLUT_KEY_UP){

         rotacionarMalha3DXCubo(-15);

			}

		}else if(selecionarBounding && ESFERA){

			if(key== GLUT_KEY_LEFT){

				 rotacionarMalha3DYEsfera(-15);

			}else if(key == GLUT_KEY_RIGHT){

				 rotacionarMalha3DYEsfera(15);

			}else if(key == GLUT_KEY_DOWN){

				 rotacionarMalha3DXEsfera(15);

			}else if(key == GLUT_KEY_UP){

				 rotacionarMalha3DXEsfera(-15);

			}


		}else if(selecionarCena){

			if(key== GLUT_KEY_LEFT){


				   rotacionarCameraEixoY(-15);
            //indiceEixoX-=15;
						//lookx = ()
				    //cout<<"eixoX: "<<indiceEixoX<<endl;
						//anglee -= 0.1f;
			//lx = sin(anglee);
			//lz = -cos(anglee);

		 }else if(key == GLUT_KEY_RIGHT){

				rotacionarCameraEixoY(15);

				//anglee += 0.1f;
		 //lx = sin(anglee);
		 //lz = -cos(anglee);

		 }else if(key == GLUT_KEY_DOWN){

			/* angley += 0.1f;
		   lz = sin(angley);
		   ly = -cos(angley);*/

		 }else if(key == GLUT_KEY_UP){

				rotacionarCameraEixoX(-15);

		 }

		}

    //EspecificaParametrosVisualizacao();
    Reshape(640,480);
		glutPostRedisplay();

}
/*
void GerenciaTeclado(unsigned char key, int x, int y){

    /*if(key == 's'){
     //cout<<"dsdsddsdss"<<endl;
         posz+=1;
				 lookz+=1;

     }else if(key == 'w'){

         posz-=1;
				 lookz-=1;

     }else if(key == 'a'){

         posx-=1;
         lookx-=1;

     }else if(key == 'q'){

         posy-=1;
				 looky-=1;

		 }else if(key == 'e'){

        posy+=1;
        looky+=1;
		 }
		 else if(key == 'd'){

         posx+=1;
         lookx+=1;

     }
		 else if(key =='q'){

         GLfloat ang = 5;

         ang = ang * M_PI/180;

         lookx = cos(ang) * (lookx - posx) - sin(ang) * (lookz-posz) + posx;
         lookz = sin(ang) * (lookx - posx) + cos(ang) * (lookz - posz) + posz;

         //cout<<"lookx: "<<lookx<<" lookz:"<<lookz<<endl;
     }else if(key  == 37){

      GLfloat ang = 5;

         ang = -(ang * M_PI/180);
         lookx = cos(ang) * (lookx - posx) - sin(ang) * (lookz-posz) + posx;
         lookz = sin(ang) * (lookx - posx) + cos(ang) * (lookz - posz) + posz;

     }

     //translada no eixo x lado negativo
       if(key == 'z'){

      	if(CUBO){

					transladarEixoCubo(-0.2f,0,0);

				}else if (ESFERA){

         transladarEixoEsfera(-0.2f,0,0);

				}else if(PIRAMIDE){


			  }


		 }

     //translada no eixo x lado positivo
		 else if(key == 'Z'){

			 if(CUBO){

				 transladarEixoCubo(0.1f,0,0);

			 }else if (ESFERA){

        transladarEixoEsfera(0.1f,0,0);

			 }else if(PIRAMIDE){


		   }

      //translada no eixo y lado negativo
		 }else if(key == 'x'){

			 if(CUBO){

				 transladarEixoCubo(0,-0.01f,0);

			 }else if (ESFERA){

         transladarEixoEsfera(0,-0.1f,0);


			 }else if(PIRAMIDE){


		   }

    //translada no eixo y lado positivo
		 }else if(key == 'X'){

			 if(CUBO){

				 transladarEixoCubo(0,0.01f,0);

			 }else if (ESFERA){

         transladarEixoEsfera(0,0.1f,0);

			 }else if(PIRAMIDE){


		   }

  //translada no eixo z lado negativo
	}else if(key == 'c'){

 			 if(CUBO){

 				 transladarEixoCubo(0,0,-0.1f);

 			 }else if (ESFERA){

          transladarEixoEsfera(0,0,-0.1f);

 			 }else if(PIRAMIDE){


 		 }//translada no eixo z lado positivo
 	 }else if(key == 'C'){

  			 if(CUBO){

  				 transladarEixoCubo(0,0,0.1f);

  			 }else if (ESFERA){

           transladarEixoEsfera(0,0,0.1f);

  			 }else if(PIRAMIDE){


  		   }


  		 }
    Reshape(640,480);
    //EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}
*/
/*
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
//camera.rotation(x, y);
cout<<"cord x: "<<x-250<<" cordy: "<<300-y<<endl;

if (button == GLUT_RIGHT_BUTTON)
     if (state == GLUT_DOWN)
        CriaMenu();

EspecificaParametrosVisualizacao();
glutPostRedisplay();
}*/
// Programa Principal

int main(int argc, char** argv)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInit(&argc, argv);

  vec3 vert;
  vertices.push_back(vert);//para começar do indice 1
  rgb.push_back(vert);//para começar do indice 1
  //bool res = loadObjFromArchive("ambienteSimulado/ex06/scan73.obj",'b');
	bool res = loadObjFromArchive("scan99-BRAND_edit_2.obj",'b');

  if(!res){

      cout<<"You should take a look at the obj file!"<<endl;

  }

	/*
  //iniciarlizarParametrosEixos();
	glutInitWindowSize(500, 600);
	glutCreateWindow("3DIR");
  glutSpecialFunc(tecladoSeta);
	glutReshapeFunc(AlteraTamanhoJanela);
  glutKeyboardFunc(GerenciaTeclado);
	glutMouseFunc(GerenciaMouse);
  glutDisplayFunc(desenharSala);
  Inicializa();
	glutMainLoop();*/
	glutInitWindowSize(640, 480);
	glutCreateWindow("FPS demo by Nghia Ho - Hit SPACEBAR to toggle FPS mode");
	  glutIgnoreKeyRepeat(1);

    glutSpecialFunc(tecladoSeta);
    glutDisplayFunc(Displays);
    glutIdleFunc(Displays);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(MouseMotion);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutIdleFunc(Idle);

    glutTimerFunc(1, Timer, 0);
		 Inicializa();

    glutMainLoop();

    return 0;

}

void saveScreenToImage(){

        //cout<<"Entre com o nome da imagem (coloque como png): ";
        //cin>>nomeImagem;

	GLfloat* OpenGLimage = new GLfloat[307200*3];
	//glReadBuffer(GL_BACK);
        nomeImagem = "pattern"+to_string(contImagem);
        nomeImagem+=".png";
        contImagem+=1;
	glReadPixels(1, 1, 640, 480,GL_RGB, GL_FLOAT, OpenGLimage);
	pngwriter PNG(640, 480, 1.0, nomeImagem.c_str());
	size_t x = 1;   // start the top and leftmost point of the window
	size_t y = 1;
	double R, G, B;

	for(size_t i=0; i<307200*3; i++)
	{
	      switch(i%3) //the OpenGLimage array look like [R1, G1, B1, R2, G2, B2,...]
	     {
		   case 2:
		         B = (double) OpenGLimage[i];
                         //cout<<"Cor blue: "<<B<<endl;
                         break;
		   case 1:
		         G = (double) OpenGLimage[i];
			 //cout<<"Cor green: "<<G<<endl;
 			 break;
		   case 0:
		         R = (double) OpenGLimage[i];
			 //cout<<"Cor red: "<<R<<endl;
		         PNG.plot(x, y, R, G, B);
		         if( x == 640 )
		         {
		               x=1;
		               y++;
		          }
		          else
		          { x++; }
		          break;
	     }
	}
	PNG.close();




}

void Grid()
{
    glPushMatrix();
    glColor3f(1,1,1);

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();
}

void Displays (void) {
    glClearColor (0.4,0.4,0.4,1.0); //clear the screen to black
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

	  g_camera.Refresh();

    desenharSala();

    glutSwapBuffers(); //swap the buffers
}

void Reshape (int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1 , 100.0); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void recalculateCentralPoints(){

	  maxx=-100;
	  maxy=-100;
	  maxz=-100;
	  minx=100;
	  miny=100;
	  minz=100;

		for(int i=1;i<vertices.size();i++){

							if(minx > vertices[i].x){

									minx=vertices[i].x;

							}
							if(miny > vertices[i].y){

									miny=vertices[i].y;

							}
							if(minz > vertices[i].z){

									minz=vertices[i].z;

							}
							if(maxx < vertices[i].x){

									maxx=vertices[i].x;

							}
							if(maxy < vertices[i].y){

									maxy=vertices[i].y;

							}
							if(maxz < vertices[i].z){

									maxz=vertices[i].z;

							}


       }

}

void testarValores(){
	float minx3 = 1000000.0f;
	float maxx3 = -1000000.0f;
	float miny3 = 1000000.0f;
	float maxy3 = -1000000.0f;

  for(int i=0;i<projection.size();i++){

/*
     cout<<"Index: "<<projection[i].ind<<" Pontos 3D: "<<vertices[projection[i].ind].x<<";"
		 <<vertices[projection[i].ind].y<<";"<<vertices[projection[i].ind].z
		 <<" Pontos 2D: "<<projection[i].points.x<<";"<<projection[i].points.y<<";"<<projection[i].points.z<<endl;

		 if(projection[i].points.x < minx3){
			 minx3 = projection[i].points.x;
		 }
		 if(projection[i].points.x > maxx3){
			 maxx3 = projection[i].points.x;
		 }
		 if(projection[i].points.y < miny3){
			 miny3 = projection[i].points.y;
			}
		 if(projection[i].points.y > maxy3){
			 maxy3 = projection[i].points.y;
		 }

*/
	}

	//cout<<"min x = "<<minx3<<"; max x = "<<maxx3<<endl;
	//cout<<"min y = "<<miny3<<"; max y = "<<maxy3<<endl;


}

void calculaCentral(){

	float range = 1.0f;

	GLfloat xis = (320-((bBox.left+bBox.width)/2));
	GLfloat yis = (((bBox.top+bBox.height)/2)-240);
	GLfloat zis = 2;

	//cout<<"ponto: "<<pro.points.x<<";"<<pro.points.y<<";"<<pro.points.z<<endl<<endl;
	//cout<<"central: "<<xis<<"; "<<yis<<endl;

	for(int i=0;i<projection.size();i++){

		if(projection[i].points.x >= xis - range && projection[i].points.x <= xis+range
		&& projection[i].points.y >= yis-range && projection[i].points.y <= yis+range && projection[i].points.z < zis){

			//cout<<"ponto central encontrado, indice = "<<pro.ind<<endl;
			cont_aux++;
			//cout<<cont_aux<<endl;
			//cout<<"ponto: "<<pro.points.x<<";"<<pro.points.y<<";"<<pro.points.z<<endl<<endl;
			BoxCenter = projection[i].ind;
			zis = projection[i].points.z;
		}
	}

}
//k --> calcula matriz de projeção;
//l --> manda o objeto para o centro da tela
//p --> chama yolo e captura informações do bounding box
//z --> leva a camera para -1 em z
void Keyboard(unsigned char key, int x, int y)
{

 if(key == 'k'){//salva valores da matriz de projeção

     salvarPontosDaProjecao(0.1f,100,widthFrame,heightFrame);
     encontrarFronteiras();
    /* string nameOfText = "pontosDeFronteira"+to_string(contadorDeArquivosText);
		 ofstream out(nameOfText);
    for(int i=0;i<sPoints.pointsFilteredTo3D.size();i++){

         GLfloat x = projection[sPoints.pointsFilteredTo3D[i].ind].points.x;
         GLfloat y = projection[sPoints.pointsFilteredTo3D[i].ind].points.y;
         GLfloat z = projection[sPoints.pointsFilteredTo3D[i].ind].points.z;
         out <<x<< ","<<y<<","<<z<<"\n";
				 //cout<<"projection "<<i<<": x = "<<projection[i].x<<" y = "<<projection[i].y<<" z = "<<projection[i].z<<endl;

    }


	  out.close();
    contadorDeArquivosText++;*/


		for(int i=0;i<verticesDeFronteira.size();i++){

			 //if(verticesDeFronteira[i] != -1){
				pontosDefronteiraSalvo.push_back(verticesDeFronteira[i]);
			// }
		}

	 verticesDeFronteira.clear();
	 projection.clear();
	 sPoints.pointsWithNoFilter.clear();
	 sPoints.pointsFilteredTo3D.clear();

 }

 else if(key == 'o'){//função que chama o SIFT, mas somente se o bouding box foi desenhado

    string parametro = "./callSift.sh "+nomeImagem+".jpg,"+to_string(bBox.left)+ ","+to_string(bBox.top) + ","+to_string((bBox.width+bBox.left)) + ","+to_string((bBox.height+bBox.top)) + " "+nomeImagem+".jpg";
    //string aux = "ddd";
		//string parametro = "./callSift.sh " +aux+" "+nomeImagem+".jpg";
		cout<<"Parametro: "<<parametro<<endl;
		system(parametro.c_str());

    string caminho = "file_"+nomeImagem+".jpg.txt";

		char * writable = new char[caminho.size() + 1];
    std::copy(caminho.begin(), caminho.end(), writable);
    writable[caminho.size()] = '\0'; // don't forget the terminating 0

    readPointsInTxt(writable);

    delete[] writable;

 }

  else if(selecionarCena && key == 'l'){

     toZero = !toZero;
		 //transladarObjeto(0.0f,0.0f,0.0f);
		 transladarObjeto(-0.5f,-0.5f,-2.0f);
		 recalculateCentralPoints();

	}else if(key == 'z'){

	 if(selecionarSala){

            transladarObjeto(-0.2f,0,0);
						recalculateCentralPoints();

        }else if(CUBO){

		 transladarEixoCubo(-0.2f,0,0);

	 }else if (ESFERA){

		transladarEixoEsfera(-0.2f,0,0);

	 }else if(PIRAMIDE){


	 }


}

else if(key == 'p'){

    saveScreenToImage();
    //string parametro = "./callYolo.sh "+nomeImagem;
		string parametro = "./callYolo_sofa.sh "+nomeImagem;
		string parametro2 = "../darknet-master/"+nomeImagem+".txt";
    system(parametro.c_str());

    char * writable = new char[parametro2.size() + 1];
    std::copy(parametro2.begin(), parametro2.end(), writable);
    writable[parametro2.size()] = '\0'; // don't forget the terminating 0
    readFileBoundingBox(writable);
		// don't forget to free the string after finished using it
		delete[] writable;
}

else if(key == 'b'){

	//aqui vem o yolo
	saveScreenToImage();
	string parametro = "./callYoloAuto.sh "+nomeImagem;
	string parametro2 = "../darknet-master/"+nomeImagem+".txt";
	system(parametro.c_str());

	char * writable = new char[parametro2.size() + 1];
	std::copy(parametro2.begin(), parametro2.end(), writable);
	writable[parametro2.size()] = '\0'; // don't forget the terminating 0
	readFileBoundingBox(writable);
	// don't forget to free the string after finished using it
	delete[] writable;

	salvarPontosDaProjecao(0.1f,100,widthFrame,heightFrame);

//	calculaCentral();


     for(int i=0;i<24;i++){

        	//autoRotacionarY(-15);
          //for(int j=0;j<100;j++);
          rotacionarMalha3DY(-15);
          //comeco
	 //aqui vem o yolo
	 saveScreenToImage();
	 string parametro = "./callYoloAuto.sh "+nomeImagem;
	 string parametro2 = "../darknet-master/"+nomeImagem+".txt";
	 system(parametro.c_str());

	 char * writable = new char[parametro2.size() + 1];
	 std::copy(parametro2.begin(), parametro2.end(), writable);
	 writable[parametro2.size()] = '\0'; // don't forget the terminating 0
	 readFileBoundingBox(writable);
	 // don't forget to free the string after finished using it
	 delete[] writable;

	 // aqui vem o sift

	 parametro = "./callSiftAuto.sh "+nomeImagem+".jpg,"+to_string(bBox.left)+ ","+to_string(bBox.top) + ","+to_string((bBox.width+bBox.left)) + ","+to_string((bBox.height+bBox.top)) + " "+nomeImagem+".jpg";
	 //string aux = "ddd";
	 //string parametro = "./callSift.sh " +aux+" "+nomeImagem+".jpg";
	 //cout<<"Parametro: "<<parametro<<endl;
	 system(parametro.c_str());

	 string caminho = "file_"+nomeImagem+".jpg.txt";

	 char * writable2 = new char[caminho.size() + 1];
	 std::copy(caminho.begin(), caminho.end(), writable2);
	 writable2[caminho.size()] = '\0'; // don't forget the terminating 0

	 readPointsInTxt(writable2);

	 delete[] writable2;

	 //aqui vai descobrir os pontos de fronteira


	 salvarPontosDaProjecao(0.1f,100,widthFrame,heightFrame);
	 encontrarFronteiras();

 for(int i=0;i<verticesDeFronteira.size();i++){

		//if(verticesDeFronteira[i] != -1){
		 pontosDefronteiraSalvo.push_back(verticesDeFronteira[i]);
		//}
 }

verticesDeFronteira.clear();
projection.clear();

sPoints.pointsWithNoFilter.clear();
sPoints.pointsFilteredTo3D.clear();


				  //fim

					desenharSala();
			    glutSwapBuffers();

		 }

}

else if(key == 'r'){

	 autoRotacionarY(-15);
	 //cout<<"rotação auto\n";


}

else if(key == 'i'){

    //proposta experimental

		saveScreenToImage();
    string parametro = "pattern"+to_string(contImagem-1)+".png";
		//string nameOfText = "pontosDeFronteira"+to_string(contImagem-1);
    realizarPropostaExperimental(parametro,"pontosDeFronteira",contadorDeArquivosText-1);



}
else if (key == 't'){

	//copiar paa aqui os pontos em pontosDefronteiraSalvo
		string nameOfText = "pontosDeFronteira"+to_string(contadorDeArquivosText);
		ofstream out(nameOfText);
		salvarPontosDaProjecao2(0.1f,100,widthFrame,heightFrame);
		for(int i=0;i<borderPoints.size();i++){

				 GLfloat x = borderPoints[i].points.x;
				 GLfloat y = borderPoints[i].points.y;
				 GLfloat z = borderPoints[i].points.z;
				 out <<x<< ","<<y<<","<<z<<"\n";

		}
		out.close();
	borderPoints.clear();
	verticesDeFronteira.clear();
	projection.clear();
	sPoints.pointsWithNoFilter.clear();
	sPoints.pointsFilteredTo3D.clear();
	pontosDefronteiraSalvo.clear();
  contadorDeArquivosText++;
/*
verticesDeFronteira.clear();
projection.clear();
sPoints.pointsWithNoFilter.clear();
sPoints.pointsFilteredTo3D.clear();
*/
}
//translada no eixo x lado positivo
else if(key == 'Z'){

        if(selecionarSala){

            transladarObjeto(0.2f,0,0);
						recalculateCentralPoints();

        }else if(CUBO){

	    transladarEixoCubo(0.2f,0,0);

	}else if (ESFERA){

	    transladarEixoEsfera(0.2f,0,0);

	}else if(PIRAMIDE){


	}

 //translada no eixo y lado negativo
}else if(key == 'x'){

	 if(selecionarSala){

            transladarObjeto(0,-0.2f,0);
						recalculateCentralPoints();

        }else if(CUBO){

		transladarEixoCubo(0,-0.2f,0);

	}else if (ESFERA){

		transladarEixoEsfera(0,-0.2f,0);


	}else if(PIRAMIDE){


	}

//translada no eixo y lado positivo
}else if(key == 'X'){

	 if(selecionarSala){

            transladarObjeto(0,0.2f,0);
						recalculateCentralPoints();

        }else if(CUBO){

		transladarEixoCubo(0,0.2f,0);

	}else if (ESFERA){

		transladarEixoEsfera(0,0.2f,0);

	}else if(PIRAMIDE){


	}

//translada no eixo z lado negativo
}else if(key == 'c'){

	if(selecionarSala){

            transladarObjeto(0,0,-0.2f);
						recalculateCentralPoints();

        }else if(CUBO){

		transladarEixoCubo(0,0,-0.2f);

	}else if (ESFERA){

		 transladarEixoEsfera(0,0,-0.2f);

	}else if(PIRAMIDE){


}//translada no eixo z lado positivo
}else if(key == 'C'){

		if(selecionarSala){

            		transladarObjeto(0,0,0.2f);
								recalculateCentralPoints();

        	}else if(CUBO){

			transladarEixoCubo(0,0,0.2f);

		}else if (ESFERA){

			transladarEixoEsfera(0,0,0.2f);

		}else if(PIRAMIDE){


		}


	}


    else if(key == 27) {
        exit(0);
    }

    else if(key == ' ' && selecionarCena) {
        g_fps_mode = !g_fps_mode;

        if(g_fps_mode) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    else if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        g_shift_down = true;
    }
    else {
        g_shift_down = false;
    }

    g_key[key] = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
    g_key[key] = false;
}

void Timer(int value)
{
    if(g_fps_mode) {
        if(g_key['w'] || g_key['W']) {
            g_camera.Move(g_translation_speed);
        }
        else if(g_key['s'] || g_key['S']) {
            g_camera.Move(-g_translation_speed);
        }
        else if(g_key['a'] || g_key['A']) {
            g_camera.Strafe(g_translation_speed);
        }
        else if(g_key['d'] || g_key['D']) {
            g_camera.Strafe(-g_translation_speed);
        }
        else if(g_mouse_left_down) {
            g_camera.Fly(-g_translation_speed);
        }
        else if(g_mouse_right_down) {
            g_camera.Fly(g_translation_speed);
        }
    }

    glutTimerFunc(1, Timer, 0);
}

void Idle()
{
    Displays();
}

void Mouse(int button, int state, int x, int y)
{

    float xx = (float)(x-widthFrame/2);///(widthFrame/2);
    float yy = (float)(heightFrame/2-y);///(heightFrame/2);
    cout<<"Cordx: "<<xx<<"  Cordy: "<<yy<<endl;
    //testarMatrizDeProjecao(0.1f,100.0f,widthFrame,heightFrame,-1.425000f,-0.015280f,3.245000f);//-1.425000 -0.015280 3.245000
    //testarMatrizDeProjecao(0.1f,100.0f,widthFrame,heightFrame,-1.393561f,-0.035000f,3.235000f);//-1.393561 -0.035000 3.235000
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {

	    CriaMenu();
            g_mouse_right_down = true;
        }
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }


}

void MouseMotion(int x, int y)
{
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

    if(g_fps_mode) {
        int dx = x - g_viewport_width/2;
        int dy = y - g_viewport_height/2;

        if(dx) {
            g_camera.RotateYaw(g_rotation_speed*dx);
        }

        if(dy) {
            g_camera.RotatePitch(g_rotation_speed*dy);
        }

        glutWarpPointer(g_viewport_width/2, g_viewport_height/2);

        just_warped = true;
    }
}
