#define PathGetHome() getenv("HOME");

char *PathCanonize(char *path){
  char *p=path;
  if (!strncmp(p, "file:", 5)) p+=5;
  else if ('~'==path[0]){
  
  }
}

bool PathIsAbsolute(char *path){

}

char *PathAbsolute(char *path){

}

char *PathAbsoluteTo(char *path, char *root){

}

char *PathRelative(char *path){

}

char *PathRelativeTo(char *path, char *root){

}
