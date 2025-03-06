extern "C" {
  // function prototypes
  void start();
  void blink();
  void counter();
}

void init() {
  start();
}

int main() 
{
  init();
  while(1)
  {
    //blink();
    counter();
  }
  return 1;
}
