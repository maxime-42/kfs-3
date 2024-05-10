

# Compiler
CC := gcc -g

# Directories
SRCDIR := src
INCDIR := include
BUILDDIR := build
TARGET := heap_test

# Files
SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS :=  -Wall -Wextra -Werror -I$(INCDIR)

# Default rule
all: $(TARGET)

# Target rule
$(TARGET): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(TARGET)

# Compile rule
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	@rm -rf $(BUILDDIR) $(TARGET)

re: clean all
# Phony targets
docker:
		# sudo systemctl restart docker 
		# sudo docker pull debian:latest
		sudo docker-compose -f docker-compose.yml build #--no-cache
		sudo docker-compose -f docker-compose.yml up --force-recreate -d #--force-recreate

stop-docker:	down
		sudo docker system prune -af
		sudo docker system prune

.PHONY: all clean