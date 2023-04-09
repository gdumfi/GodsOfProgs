WORKDIR C:\Users\gdumf\Desktop\proj\GodsOfProgs

COPY *.cpp C:\Users\gdumf\Desktop\proj\GodsOfProgs
COPY *.h C:\Users\gdumf\Desktop\proj\GodsOfProgs
COPY *.pro C:\Users\gdumf\Desktop\proj\GodsOfProgs

RUN qmake Multy_serv.pro
RUN make

ENTRYPOINT [".\Multy_serv"]