GLuint texture;
//Load Bitmap
SDL_Surface* bmpFile = SDL_LoadBMP("data/test.bmp");
 
 /* Standard OpenGL texture creation code */
 glPixelStorei(GL_UNPACK_ALIGNMENT,4);
  		
  		glGenTextures(1,&texture);
  		glBindTexture(GL_TEXTURE_2D,texture);
  		 
  		 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
  		 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);
  		  		
  		 gluBuild2DMipmaps(GL_TEXTURE_2D,3,bmpFile->w, bmpFile->h,GL_BGR_EXT, GL_UNSIGNED_BYTE,bmpFile->pixels);

  		  		       
  		  //Free surface after using it
  		  SDL_FreeSurface(bmpFile);
