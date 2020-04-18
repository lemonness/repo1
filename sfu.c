#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "client.c"

unsigned char s[17] = {0};  
unsigned char d[17] = {0};
/*
void printf_unchar(unsigned char str[])
{
    int i = 0;
    for(i = 0;i < 16;i++) {             
        printf("%02x",str[i]);
    }
    printf("\n");
}*/

int main()
{
    //int argc, char *argv[]
    int skfd,cnfd,addr_len;
    struct sockaddr_in srv_addr,clt_addr;
    //int portnumber;
    int i = 0;
    //if(2 != argc || 0 > (portnumber = atoi(argv[1])))
    //{
    //     printf("Usage:%s port\n",argv[0]);
     //    exit(1);
    //}
    
    /* 创建IPv4的流式套接字描述符 */
    if(-1 == (skfd = socket(AF_INET,SOCK_STREAM,0)))
    {
         perror("Socket Error:");
         exit(1);
    }

    /* 填充服务器端sockaddr地址结构 */
    bzero(&srv_addr,sizeof(struct sockaddr_in));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = htons(5679);

    /* 将套接字描述符skfd和地址信息结构体绑定起来 */
    if(-1 == bind(skfd,(struct sockaddr *)(&srv_addr),sizeof(struct sockaddr)))
    {
         perror("Bind error:");
         exit(1);
    }

    /* 将skfd转换为被动建通模式 */
    if(-1 == listen(skfd,4))
    {
         perror("Listen error:");
         exit(1);
    }
    int usenum = 0;
    while(1){
    	/* 调用accept,服务器端一直阻塞，直到客户程序与其建立连接成功为止*/
    	addr_len = sizeof(struct sockaddr_in);
    	if(-1 == (cnfd=accept(skfd,(struct sockaddr *)(&clt_addr),&addr_len)))
    	{
    	    perror("Accept error:");
    	    exit(1);
   	    }
	usenum++;
	printf("用户%d上线 ...!\n",usenum);
   	//printf("地址为%s:%u的用户上线 ...!\n",inet_ntoa(clt_addr.sin_addr),ntohs(clt_addr.sin_port));
 
    while(1){
 	/*接收*/   
    	if(-1 == read(cnfd,s,sizeof(s))){
    	    printf("Recv Error:");
   	    }
        char reslut = 'a';
        if(s[0] == 'k')
            /*go验证*/
                reslut = goverify();
        if(s[0] == 'g')
            break;

        /*发送*/
        d[0] = reslut;
        if(-1 == write(cnfd,d,sizeof(d))){
            perror("Send error:");
            exit(1);
        }
    }
    	/* 拆除TCP连接 */
	printf("用户%d退出 ...!\n\n",usenum);
    	shutdown(cnfd,SHUT_RDWR);
    	close(cnfd);
    }
    shutdown(skfd,SHUT_RDWR);   
    close(skfd);
    exit(0);
}

