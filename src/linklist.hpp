struct node
{
    int x, y;
    node *next;
};

class linklist
{
  public:
    linklist(int x = 0, int y = 0);
    ~linklist();
    void setcoordinates(node *p, int x, int y);
    void addnode(int x, int y);
    void deletenode(node *p);
    int getx(node *p);
    int gety(node *p);
    int getlength();
    node *gethead();
    node *getnext(node *p);

  private:
    node *head;
    int length;
};