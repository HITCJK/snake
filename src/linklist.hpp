struct node
{
    int x, y;
    node *next;
};

class linklist
{
  public:
    linklist(int x, int y);
    ~linklist();
    void setcoordinates(node *p,int x, int y);
    void addnode(int x, int y);
    int getx(node *p);
    int gety(node *p);
    int getlength();
    node *gethead();
    node *getnext(node *p);

  private:
    node *head;
    int length;
};