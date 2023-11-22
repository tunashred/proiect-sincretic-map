FROM busybox:latest

COPY src/runme .
RUN chmod +x runme

ENTRYPOINT ["./runme"]
CMD ["3"]
