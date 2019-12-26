unsigned char linearisation(float in);

//input values corresponding to 0 - 255 outputs
static const float __attribute__((__progmem__)) linearisationVals [256] = {0, 1.0, 1.603806399, 2.114258743, 2.572194967, 2.994663698, 3.390861701, 3.76646828, 4.125302748, 4.47009003, 4.802860802, 5.125179908, 5.438285696, 5.743179559, 6.04068593, 6.331493904, 6.616186948, 6.895264654, 7.169158997, 7.438246714, 7.70285889, 7.963288489, 8.219796335, 8.472615936, 8.721957402, 8.968010662, 9.21094813, 9.450926927, 9.688090752, 9.922571467, 10.15449044, 10.38395971, 10.61108297, 10.83595643, 11.05866958, 11.27930583, 11.49794308, 11.71465424, 11.92950768, 12.14256759, 12.35389438, 12.56354496, 12.77157304, 12.97802936, 13.18296196, 13.38641634, 13.58843566, 13.78906092, 13.9883311, 14.1862833, 14.38295289, 14.57837358, 14.77257756, 14.96559559, 15.15745709, 15.34819021, 15.53782195, 15.72637814, 15.91388362, 16.10036219, 16.28583675, 16.47032931, 16.65386103, 16.83645231, 17.01812277, 17.19889133, 17.37877626, 17.55779516, 17.73596504, 17.91330231, 18.08982286, 18.26554204, 18.44047469, 18.61463518, 18.78803744, 18.96069495, 19.13262076, 19.30382755, 19.47432761, 19.64413286, 19.81325487, 19.98170488, 20.14949381, 20.31663227, 20.48313057, 20.64899874, 20.81424655, 20.97888347, 21.14291876, 21.30636141, 21.46922019, 21.63150363, 21.79322007, 21.9543776, 22.11498414, 22.27504741, 22.43457493, 22.59357405, 22.75205194, 22.91001561, 23.06747189, 23.22442745, 23.38088884, 23.53686241, 23.69235442, 23.84737095, 24.00191797, 24.15600131, 24.30962667, 24.46279964, 24.61552569, 24.76781015, 24.91965827, 25.07107518, 25.22206591, 25.37263537, 25.52278838, 25.67252969, 25.82186391, 25.9707956, 26.1193292, 26.26746909, 26.41521955, 26.56258477, 26.7095689, 26.85617597, 27.00240995, 27.14827475, 27.2937742, 27.43891205, 27.58369199, 27.72811764, 27.87219258, 28.0159203, 28.15930424, 28.30234778, 28.44505423, 28.58742686, 28.72946889, 28.87118346, 29.01257367, 29.15364259, 29.29439321, 29.43482848, 29.57495131, 29.71476456, 29.85427103, 29.9934735, 30.13237468, 30.27097727, 30.40928389, 30.54729715, 30.68501961, 30.82245379, 30.95960216, 31.09646718, 31.23305125, 31.36935674, 31.50538599, 31.6411413, 31.77662495, 31.91183917, 32.04678616, 32.18146809, 32.31588712, 32.45004534, 32.58394485, 32.71758769, 32.85097589, 32.98411145, 33.11699633, 33.24963248, 33.38202181, 33.51416622, 33.64606757, 33.77772769, 33.90914841, 34.04033152, 34.17127878, 34.30199194, 34.43247273, 34.56272284, 34.69274396, 34.82253773, 34.95210581, 35.08144979, 35.21057129, 35.33947187, 35.46815309, 35.59661648, 35.72486358, 35.85289587, 35.98071484, 36.10832195, 36.23571865, 36.36290637, 36.48988651, 36.61666048, 36.74322965, 36.86959538, 36.99575903, 37.12172192, 37.24748537, 37.37305068, 37.49841914, 37.62359201, 37.74857056, 37.87335603, 37.99794964, 38.12235261, 38.24656614, 38.37059143, 38.49442964, 38.61808194, 38.74154949, 38.86483341, 38.98793483, 39.11085486, 39.23359462, 39.35615518, 39.47853762, 39.60074301, 39.72277242, 39.84462687, 39.96630741, 40.08781505, 40.20915082, 40.33031571, 40.45131071, 40.57213681, 40.69279497, 40.81328617, 40.93361134, 41.05377145, 41.17376741, 41.29360015, 41.41327059, 41.53277964, 41.65212818, 41.77131712, 41.89034732, 42.00921967, 42.12793502, 42.24649423, 42.36489815, 42.48314761, 42.60124345, 42.71918648, 42.83697753, 42.9546174, 43.07210688, 43.18944678, 43.30663788, 43.42368096, 43.54057679, 43.65732612};