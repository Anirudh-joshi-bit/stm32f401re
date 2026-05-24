#include "commons.h"
#include "USART.h"
#include "queue.h"

void __usart2_init ();
void printf(const char *msg, ...);

// make a queue and push any struct into it .... this is possible

// struct one
typedef struct {
  uint16_t data11;
  uint16_t data12;
}s1;

// struct two
typedef struct {
  uint32_t *data21;
  uint16_t *data22;
}s2;


// 00 bytes buffer
uint8_t array [100];
uint32_t array_size = 100;
queue_t q;


int main() {

  __usart1_init();

  s1 s11, s12, s13, s14;
  s2 s21, s22, s23, s24;
  queue_init (&q, (void *)array, array_size);
   

  // push and pop
  queue_push (&q, (void *)&s11, sizeof (s11));
  queue_push (&q, (void *)&s21, sizeof (s21));
  queue_push (&q, (void *)&s12, sizeof (s12));
  queue_push (&q, (void *)&s22, sizeof (s22));

  // queue -> s1, s2, s1, s2

  queue_pop (&q, sizeof (s2));
  queue_pop (&q, sizeof (s1));
  queue_pop (&q, sizeof (s2));
  //queue_pop (&q, sizeof (s1));

  printf ("size of queue is -> %d\n\r", queue_size(&q));
  printf ("size of s1 is -> %d\n\r", sizeof (s1));


  while (1)
    ;
}
