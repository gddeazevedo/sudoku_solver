import csv
from matplotlib import pyplot as plt


def plot_exec_time_per_instance_graph():
    x_points = []
    y_points = []
    x_label = ''
    y_label = ''


def plot_operations_per_instance_graph():
    pass


def read_file_and_plot_graph():
    x_points = []
    y_points = []
    x_label = ''
    y_label = ''

    with open('./data.csv') as file:
        csv_reader = csv.reader(file, delimiter=',')
        line = 0

        for row in csv_reader:
            if line == 0:
                x_label = row[0]
                y_label = row[1]
            else:
                x_points.append(int(row[0]))
                y_points.append(float(row[1]))
            line += 1

    plt.plot(x_points, y_points)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title('Time x Words')
    plt.show()


if __name__ == '__main__':
    read_file_and_plot_graph()