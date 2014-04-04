#ifndef _MAP_H_
#define _MAP_H_

class map{
   public:

      /****************
       * Constructors *
       ****************/

      map();
      ~map();

      void hello();

   private:

      float *mem;
      float *x1, *y1, *x2, *y2;       // line parameters
      float *tmp, *radii, *centers;   // circle parameters

};

#endif
