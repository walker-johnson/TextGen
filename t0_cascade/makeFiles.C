#include "generate_txtgen_w_t0.C"

void generate_txtgen_w_t0(UInt_t ncap, UInt_t nevt, string file);

void makeFiles(){
  Int_t caps = 10;
  Int_t events = 0;
  Int_t run = 0;

  Int_t e_per = 200;

  while(events < 1000){

    char name[18] = "10_captures_file_";

    char c[10];

    sprintf(c, "%d", run);

    string filename = strcat(name, c);
 
    generate_txtgen_w_t0(caps,e_per, filename);

    events += e_per;
    run += 1;

  }
}
