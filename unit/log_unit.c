#include "ez_log.h"

int main (argc, argv)
  int argc;
  char* argv [];
{
  // test ez_logger_new ()
#if 0
  {
    bool err = false;
    pez_logger logger = ez_logger_new (NULL);
    if (! logger) {
      println ("error create new logger!");
      return 0;
    }
    println ("successful");
    ez_logger_despose (&logger);
    println ("despose ok!");

  }
#endif // 0

  // test ez_logger_new ()
  {
    bool err = false;
    pez_logger logger = ez_logger_new (NULL);
    int i = 0;
    if (! logger) {
      println ("error create new logger!");
      return 0;
    }

    println ("successful");
    for (; i < 100; i ++)
      ez_logger_log (logger, "hello, world   ");

    for (i = 0; i < 100; i ++)
      ez_logger_logf (logger, "%s\n", "hello, world");

    ez_logger_despose (&logger);
    println ("despose ok!");

  }

  return 0;

}
