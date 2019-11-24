
void salvarPontosDaProjecao(GLfloat n,GLfloat f,GLfloat w,GLfloat h){
     //cout<<n<<" "<<f<<" "<<w<<" "<<h<<" "<<px<<" "<<py<<" "<<pz<<endl;

     setParametros(n,f);
     calculaCantos(w,h);

      for(int i=1;i<vertices.size();i++){

           calculaMatrizDeProjecao(vertices[i].x,vertices[i].y,vertices[i].z,i);

      }


}

void salvarPontosDaProjecao2(GLfloat n,GLfloat f,GLfloat w,GLfloat h){
     //cout<<n<<" "<<f<<" "<<w<<" "<<h<<" "<<px<<" "<<py<<" "<<pz<<endl;

     setParametros(n,f);
     calculaCantos(w,h);

      for(int i=0;i<pontosDefronteiraSalvo.size();i++){

           calculaMatrizDeProjecao2(vertices[pontosDefronteiraSalvo[i]].x,vertices[pontosDefronteiraSalvo[i]].y,vertices[pontosDefronteiraSalvo[i]].z);

      }


}
