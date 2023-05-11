#include "image.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Usage: %s <image_file>\n", argv[0]);
    return 1;
  }

  Image image = lire_fichier_image(argv[1]);
  ecrire_image(image);

  return 0;
}