#!/bin/bash
#SBATCH -J mandel
#SBATCH -o mandel_%j.out
#SBATCH -e mandel_%j.err
#SBATCH -N 1
#SBATCH -n 4
#SBATCH -C cpu
#SBATCH --time=00:30:00
#SBATCH --qos=debug
#SBATCH --account=m4776

srun ./mandelbrot > output.txt