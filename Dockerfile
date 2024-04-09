# Use the official ubuntu image as the base image
FROM debian:stable as builder

# Install dependencies
RUN apt update && apt install -fy gcc

# Copy in and build target
COPY snote.c snote.c

# Compile the source code
RUN gcc -o snote snote.c

# Image to test the binary
FROM debian:stable as target

# Copy the binary from the builder image
COPY --from=builder /snote /snote

# Set to fuzz
CMD ["/snote", "subject", "@@"]
