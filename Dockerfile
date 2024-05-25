FROM ubuntu:18.04
FROM gcc:latest

# Устанавливаем рабочую директорию внутри контейнера
WORKDIR /app

RUN apt-get update && apt-get install -y nano

#RUN apt-get install -r requirements.txt

# Копируем исходный код внутрь контейнера
COPY courier ./courier
COPY order ./order
COPY routes ./routes
COPY server ./server
COPY main.cpp .
COPY CMakeLists.txt .
COPY requirments.txt .


#RUN apt-get update && \
#    apt-get install -y libboost-dev libboost-program-options-dev \ cmake \ nlohmann-json-dev
RUN apt-get update
RUN apt-get install -y libboost-dev
RUN apt-get install -y cmake
RUN apt-get install sudo -y
RUN sudo apt-get install nlohmann-json3-dev
RUN sudo apt-get install -y libpqxx-dev





RUN mkdir build
RUN cd build
CMD ["/bin/bash"]
#RUN cmake ..
#RUN make
#RUN cd bin.dbg
#CMD ["./main"]