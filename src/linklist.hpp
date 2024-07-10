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
    void setcoordinates(int index, int x, int y);
    void addnode(int x, int y);
    void deletenode(int index);
    int getx(int index);
    int gety(int index);
    int getlength();
  private:
    node *head;
    int length;
};