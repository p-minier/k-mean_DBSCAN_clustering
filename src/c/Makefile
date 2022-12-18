CC = gcc
EXEC = dsbcan kmean
OBJDIR = .obj
BINDIR = bin
OUTDIR = output
SRCDIR = src
ADDLIB = -lm
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic -g -O0
DBSOBJ = cloud.o cluster.o common.o inout.o point.o test.o dsbcan.o
KMNOBJ = cloud.o cluster.o common.o inout.o point.o test.o kmean.o

all : $(OBJDIR) $(BINDIR) $(OUTDIR) $(EXEC)

dsbcan : $(DBSOBJ) $(OBJDIR) $(BINDIR)
	cd $(OBJDIR); $(CC) $(CFLAGS) -o ../$(BINDIR)/$@ $(DBSOBJ) $(ADDLIB); cd ..

kmean : $(KMNOBJ) $(OBJDIR) $(BINDIR)
	cd $(OBJDIR); $(CC) $(CFLAGS) -o ../$(BINDIR)/$@ $(KMNOBJ) $(ADDLIB); cd ..

%.o : $(SRCDIR)/%.c
	$(CC) -o $(OBJDIR)/$@ -c $<

$(OBJDIR) $(BINDIR) $(OUTDIR):
	mkdir $@

clean :
	rm -rf $(OBJDIR)

mrproper : clean
	rm -rf $(BINDIR)