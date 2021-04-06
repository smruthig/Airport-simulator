struct que* insert_queue(int item, struct que* first);
struct que* del_land( struct que* first);
struct que* del_take( struct que* first);
int count_queue(struct que* first);
float delay(float b);
int sum(struct plane* a,int tot_time);
int access_array(struct plane* a,int tot_time);
void sim(int tot_time, int maxarr, int maxdep, float arrrate, float deprate);
