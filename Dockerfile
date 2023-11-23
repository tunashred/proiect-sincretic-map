FROM busybox:latest

COPY src/hanoi .
RUN chmod +x hanoi

ENTRYPOINT ["./hanoi"]
CMD ["3"]
