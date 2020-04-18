#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

unsigned char dhash[17] = {0};
unsigned char shash[17] = {0}; 
unsigned char hash[17] = {0};
unsigned char rnum[16] = {0};
char inst[6] = {0};

void printf_unchar(unsigned char str[])
{
    int i = 0;
    for(i = 0;i < 16;i++) {             
        printf("%02x",str[i]);
    }
    printf("\n");
}

void int_to_unchar(int num)
{
    int k = 0;
    int i = 0;
    for(i = 0;num > 0;i++)
    {
        k = num % 10;
        num = num / 10;
        rnum[i] = k;
    }
    for(;i < 16;i++)
	rnum[i] = 0;
    printf("发送的随机数为:");
    printf_unchar(rnum);
}

void rnum_xor_hash(unsigned char hash[])
{
    /*哈希异或随机数*/
    int i = 0;
    for(i = 0;i < 16;i++)       
        hash[i] = rnum[i] ^ hash[i];  
}

void read_stored_hash(char *filename)
{
    FILE *file = NULL;
    file = fopen(filename, "r");
    int i = 0;
    for(i = 0;i < 16;i++) 
        hash[i] = fgetc(file);
    fclose(file);
}

int verify(unsigned char rehash[])
{
    int flag = 0;
    int i = 0;
    for(i = 0;i < 16;i++)
    if(hash[i] != rehash[i]) 
        flag = 1;
    return flag;
}

char goverify()
{
    int skfd;    
    struct sockaddr_in server_addr;
    struct hostent *host;
    int portnumber,nbytes;

    /* 创建socket描述符 */
    if(-1 == (skfd = socket(AF_INET,SOCK_STREAM,0)))
    {
         perror("Socket Error:");
         exit(1);
    }

    /* 客户端填充需要连接的服务器的地址信息结构体 */
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    // server_addr.sin_addr = *((struct in_addr *)gethostbyname("192.168.1.200")->h_addr);
    //树莓派ip地址上面

    /* 客户端调用connect主动发起连接请求 */
    if(-1 == connect(skfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)))
    {
         perror("Connect Error:");
         exit(1);
    }

    /*生成随机数发送给证明者*/
    int num;
    srand((unsigned)time(NULL));
    num = rand();
    if(-1 == write(skfd,&num,sizeof(num))){
        printf("Send error:");
        exit(1);
    }
    int_to_unchar(num);

    /*接收静态哈希*/
    if(-1 == read(skfd,shash,sizeof(shash))){
         perror("Recv Error:");
    }   
    printf("接收到的静态哈希为:");
    printf_unchar(shash);

    /*接收累计哈希*/
    if(-1 == read(skfd,dhash,sizeof(dhash))){
         perror("Recv Error:");
    }
    printf("接收到的累计哈希为:");
    printf_unchar(dhash);

    /*得到预期内容并与随机数异或*/
    read_stored_hash("shash.txt");
    rnum_xor_hash(hash);
    printf("预期的静态哈希为:");
    printf_unchar(hash);

    /*验证静态哈希*/
    int sre = 0;
    if(verify(shash) == 0){
	    printf("返回的静态哈希与预期值相同，代码完整\n");
    }else{
	sre = 1;
	    printf("返回的静态哈希与预期值不同，代码已被修改\n");
    }
      
    /*得到预期内容并与随机数异或*/
    read_stored_hash("hash.txt"); 
    rnum_xor_hash(hash);
    printf("预期的动态哈希为:");
    printf_unchar(hash);

    
    /*验证动态哈希*/
    int dre = 0;
    if(verify(dhash) == 0){
	    printf("返回的哈希与预期值相同，运行正确\n\n");
    }else{
	dre = 1;
	    printf("返回的哈希与预期值不同，遭到控制流攻击\n\n");
    }
    char re = '0';
    if(sre == 0 && dre == 1){
	re = '1';
    }
    if(sre == 1 && dre == 0){
	re = '2';
    }
    if(sre == 1 && dre == 1){
	re = '3';
    }

    /* 拆除TCP连接 */
    shutdown(skfd,SHUT_RDWR);
    close(skfd);
    return re;
}

