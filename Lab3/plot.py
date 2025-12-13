import pandas as pd
import matplotlib.pyplot as plt

def plot_benchmark_results(file_path='THRESHOLD.csv'):

    df = pd.read_csv(file_path, sep=';')

    df_renamed = df.rename(columns={
        'count': 'N',
        'insertion_avg_ns': 'Insertion Sort (ns)',
        'quick_avg_ns': 'Quick Sort (ns)'
    })

    plt.style.use('default')
    fig, ax = plt.subplots(figsize=(10, 6))

    plt.rcParams['font.family'] = 'serif'
    plt.rcParams['font.serif'] = ['Times New Roman']
    plt.rcParams['font.size'] = 14

    ax.plot(df_renamed['N'], df_renamed['Insertion Sort (ns)'],
             label='Insertion Sort', marker='', linestyle='-', color='blue')
    ax.plot(df_renamed['N'], df_renamed['Quick Sort (ns)'],
             label='Quick Sort', marker='', linestyle='-', color='red')

    ax.grid(True, linestyle='--', alpha=0.6)

    ax.set_xlabel('N (Размер массива)', fontsize=14, fontfamily='serif')
    ax.set_ylabel('Время, [нс]', fontsize=14, fontfamily='serif')

    ax.legend(loc='best', frameon=True, fancybox=True, shadow=False, fontsize=14, prop={'family': 'serif'})

    legend_texts = ax.get_legend().get_texts()
    for text in legend_texts:
        text.set_fontfamily('serif')
        text.set_size(14)

    for tick in ax.xaxis.get_major_ticks():
        tick.label1.set_fontfamily('serif')
        tick.label1.set_fontsize(14)
    for tick in ax.yaxis.get_major_ticks():
        tick.label1.set_fontfamily('serif')
        tick.label1.set_fontsize(14)

    plt.tight_layout()
    output_image_path = file_path.rsplit('.', 1)[0] + '.png'
    plt.savefig(output_image_path, dpi=300, bbox_inches='tight')
    print(f"График сохранён в файл: {output_image_path}")
    plt.show()

plot_benchmark_results('THRESHOLD.csv')