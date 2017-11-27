#include "darknet.h"

#include <sys/time.h>

void demo_art(char *cfgfile, char *weightfile, int cam_index)
{
    list *options = read_data_cfg("cfg/coco.data");
    char *name_list = option_find_str(options, "names", "data/names.list");
    char **names = get_labels(name_list);
    image **alphabet = load_alphabet();
#ifdef OPENCV
    network *net = load_network(cfgfile, weightfile, 0);
    set_batch_network(net, 1);

    srand(2222222);
    CvCapture * cap;

    cap = cvCaptureFromCAM(cam_index);

    char *window = "ArtJudgementBot9000!!!";
    if(!cap) error("Couldn't connect to webcam.\n");
    cvNamedWindow(window, CV_WINDOW_NORMAL); 
    cvResizeWindow(window, 512, 512);
    int i;
    int idx[] = {37, 401, 434};
    int n = sizeof(idx)/sizeof(idx[0]);
    layer l = net->layers[net->n-1];

    box *boxes = calloc(l.w*l.h*l.n, sizeof(box));
    float **probs = calloc(l.w*l.h*l.n, sizeof(float *));
    while(1){
        image in = get_image_from_stream(cap);
        image in_s = resize_image(in, net->w, net->h);
        show_image(in, window);
	
        float *p = network_predict(net, in_s.data);
	get_region_boxes(l, in.w, in.h, net->w, net->h, 0.24, probs, boxes, 0, 0, 0, 0.5, 1);
	draw_detections(in, l.w*l.h*l.n, 0.24, boxes, probs, 0, names, alphabet, l.classes);
        // printf("\033[2J");
        // printf("\033[1;1H");

        float score = 0;
        for(i = 0; i < n; ++i){
            float s = p[idx[i]];
            if (s > score) score = s;
        }
        score = score;
        printf("I APPRECIATE THIS ARTWORK: %10.7f%%\n", score*100);
        printf("[");
	int upper = 30;
        for(i = 0; i < upper; ++i){
            printf("%c", ((i+.5) < score*upper) ? 219 : ' ');
        }
        printf("]\n");

        free_image(in_s);
        free_image(in);

        cvWaitKey(1);
    }
#endif
}


void run_art(int argc, char **argv)
{
    int cam_index = find_int_arg(argc, argv, "-c", 0);
    char *cfg = argv[2];
    char *weights = argv[3];
    demo_art(cfg, weights, cam_index);
}

