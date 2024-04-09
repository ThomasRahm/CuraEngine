// Copyright (c) 2023 UltiMaker
// CuraEngine is released under the terms of the AGPLv3 or higher

#ifndef TREESUPPORTTIPGENERATOR_H
#define TREESUPPORTTIPGENERATOR_H

#include "TreeModelVolumes.h"
#include "TreeSupport.h"
#include "TreeSupportBaseCircle.h"
#include "TreeSupportElement.h"
#include "TreeSupportEnums.h"
#include "TreeSupportSettings.h"
#include "boost/functional/hash.hpp" // For combining hashes
#include "polyclipping/clipper.hpp"
#include "settings/EnumSettings.h"
#include "sliceDataStorage.h"
#include "utils/Coord_t.h"
#include "utils/polygon.h"
#include "TreeSupportCradle.h"

namespace cura
{


class TreeSupportTipGenerator
{
public:
    TreeSupportTipGenerator(const SliceMeshStorage& mesh, TreeModelVolumes& volumes_);

    /*!
     * \brief Generate tips, that will later form branches
     *
     * \param storage[in] Background storage, required for adding roofs.
     * \param mesh[in] The mesh that is currently processed. Contains the overhangs.
     * \param move_bounds[out] The storage for the tips.
     * \param additional_support_areas[out] Areas that should have been roofs, but are now support, as they would not generate any lines as roof. Should already be initialised.
     * \param placed_support_lines_support_areas[out] Support-lines that were already placed represented as the area the lines will take when printed.
     * \param support_free_areas[out] Areas where no support (including roof) of any kind is to be drawn.
     * \param cradle_data_export[out] Generated cradle lines.
     * \return All lines of the \p polylines object, with information for each point regarding in which avoidance it is currently valid in.
     */
    void generateTips(
        SliceDataStorage& storage,
        const SliceMeshStorage& mesh,
        std::vector<std::set<TreeSupportElement*>>& move_bounds,
        std::vector<Polygons>& additional_support_areas,
        std::vector<std::vector<FakeRoofArea>>& placed_fake_roof_areas,
        std::vector<Polygons>& support_free_areas,
        std::vector<std::vector<TreeSupportCradle*>>& cradle_data_export);

private:
    enum class LineStatus
    {
        INVALID,
        TO_MODEL,
        TO_MODEL_GRACIOUS,
        TO_MODEL_GRACIOUS_SAFE,
        TO_BP,
        TO_BP_SAFE
    };

    struct UnsupportedAreaInformation
    {
        UnsupportedAreaInformation(const Polygons area, size_t index, size_t height, coord_t accumulated_supportable_overhang) :
            area{ area },
            index{ index },
            height{ height },
            accumulated_supportable_overhang { accumulated_supportable_overhang }
        {
        }
        const Polygons area;
        size_t index;
        size_t height;
        coord_t accumulated_supportable_overhang;
    };

    using LineInformation = std::vector<std::pair<Point2LL, TreeSupportTipGenerator::LineStatus>>;

    /*!
     * \brief Converts a Polygons object representing a line into the internal format.
     *
     * \param polylines[in] The Polyline that will be converted.
     * \param layer_idx[in] The current layer.
     * \return All lines of the \p polylines object, with information for each point regarding in which avoidance it is currently valid in.
     */
    std::vector<LineInformation> convertLinesToInternal(Polygons polylines, LayerIndex layer_idx);

    /*!
     * \brief Converts lines in internal format into a Polygons object representing these lines.
     *
     * \param lines[in] The lines that will be converted.
     * \return All lines of the \p lines object as a Polygons object.
     */
    Polygons convertInternalToLines(std::vector<TreeSupportTipGenerator::LineInformation> lines);

    /*!
     * \brief Returns a function, evaluating if a point has to be added now. Required for a splitLines call in generateInitialAreas.
     *
     * \param current_layer[in] The layer on which the point lies
     * \return A function that can be called to evaluate a point.
     */
    std::function<bool(std::pair<Point2LL, TreeSupportTipGenerator::LineStatus>)> getEvaluatePointForNextLayerFunction(size_t current_layer);

    /*!
     * \brief Evaluates which points of some lines are not valid one layer below and which are. Assumes all points are valid on the current layer. Validity is evaluated using
     * supplied lambda.
     *
     * \param lines[in] The lines that have to be evaluated.
     * \param evaluatePoint[in] The function used to evaluate the points.
     * \return A pair with which points are still valid in the first slot and which are not in the second slot.
     */
    std::pair<std::vector<LineInformation>, std::vector<LineInformation>> splitLines(
        std::vector<LineInformation> lines,
        std::function<bool(std::pair<Point2LL, TreeSupportTipGenerator::LineStatus>)> evaluatePoint); // assumes all Points on the current line are valid

    /*!
     * \brief Ensures that every line segment is about distance in length. The resulting lines may differ from the original but all points are on the original
     *
     * \param input[in] The lines on which evenly spaced points should be placed.
     * \param distance[in] The distance the points should be from each other.
     * \param min_points[in] The amount of points that have to be placed. If not enough can be placed the distance will be reduced to place this many points.
     * \param enforce_distance[in] If points should not be added if they are closer than distance to other points.
     * \return A Polygons object containing the evenly spaced points. Does not represent an area, more a collection of points on lines.
     */
    Polygons ensureMaximumDistancePolyline(const Polygons& input, coord_t distance, size_t min_points, bool enforce_distance) const;

    /*!
     * \brief Creates a valid CrossInfillProvider
     * Based on AreaSupport::precomputeCrossInfillTree, but calculates for each mesh separately
     * \param mesh[in] The mesh that is currently processed.
     * \param line_distance[in] The distance between the infill lines of the resulting infill
     * \param line_width[in] What is the width of a line used in the infill.
     * \return A valid CrossInfillProvider.
     */
    std::shared_ptr<SierpinskiFillProvider> getCrossFillProvider(const SliceMeshStorage& mesh, coord_t line_distance, coord_t line_width);

    /*!
     * \brief Provides areas that do not have a connection to the buildplate or a certain height.
     * \param layer_idx The layer said area is on.
     * \param idx_of_area_below The index of the area below. Only areas that rest on this area will be returned
     * \return A vector containing the areas, how many layers of material they have below them and the idx of each area usable to get the next one layer above.
     */
    std::vector<UnsupportedAreaInformation> getUnsupportedArea(LayerIndex layer_idx, size_t idx_of_area_below);

    /*!
     * \brief Provides areas that do not have a connection to the buildplate or any other non support material below it.
     * \param layer_idx The layer said area is on.
     * \return A vector containing the areas, how many layers of material they have below them (always 0) and the idx of each area usable to get the next one layer above.
     */
    std::vector<UnsupportedAreaInformation> getFullyUnsupportedArea(LayerIndex layer_idx);

    /*!
     * \brief Calculates which parts of the model to not connect with the buildplate and how many layers of material is below them (height).
     * Results are stored in a cache.
     * Only area up to the required maximum height are stored.
     * \param mesh[in] The mesh that is currently processed.
     */
    void calculateFloatingParts(const SliceMeshStorage& mesh);

    /*!
     * \brief Generate the center points of all generated cradles.
     * \param shadow_data[in] The accumulated model of given pointy overhangs
     * \returns The accumulated model of given pointy overhangs
     */
    std::vector<std::vector<std::vector<Polygons>>> generateCradleCenters(const SliceMeshStorage& mesh);

    /*!
     * \brief Generate lines from center and model information
     * Only area up to the required maximum height are stored.
     * \param shadow_data[in] The accumulated model of given pointy overhangs
     */
    void generateCradleLines(std::vector<std::vector<std::vector<Polygons>>>& shadow_data);

    /*!
     * \brief Ensures cradle-lines do not intersect with each other.
     */
    void cleanCradleLineOverlaps();

    /*!
     * \brief Finishes the cradle areas that represent cradle base and lines and calculates overhang for them.
     * \param shadow_data[in] The accumulated model of given pointy overhangs
     * \param support_free_areas[out] Areas where support will have to be removed, to guarantee that a line is around it.
     */
    void generateCradleLineAreasAndBase(std::vector<std::vector<std::vector<Polygons>>>& shadow_data, std::vector<Polygons>& support_free_areas);


    /*!
     * \brief Generate a cradle to stabilize pointy overhang
     * \param mesh[in] The mesh that is currently processed.
     * \param support_free_areas[out] Areas where no support may be.
     */
    void generateCradle(const SliceMeshStorage& mesh, std::vector<Polygons>& support_free_areas);

    /*!
     * \brief Drops overhang areas further down until they are valid (at most max_overhang_insert_lag layers)
     * \param mesh[in] The mesh that is currently processed.
     * \param result[out] The dropped overhang ares
     * \param roof[in] Whether the result is for roof generation.
     */
    void dropOverhangAreas(const SliceMeshStorage& mesh, std::vector<Polygons>& result, bool roof);

    /*!
     * \brief Calculates which areas should be supported with roof, and saves these in roof support_roof_drawn
     * \param mesh[in] The mesh that is currently processed.
     */
    void calculateRoofAreas(const SliceMeshStorage& mesh);

    /*!
     * \brief Add a point as a tip
     * \param move_bounds[out] The storage for the tips.
     * \param p[in] The point that will be added and its LineStatus.
     * \param dtt[in] The distance to top the added tip will have.
     * \param hidden_radius_increase[in] Additional bp increases hidden from the collision calculation. Used to ensure branches are large enough to reach initial layer diameter.
     * \param insert_layer[in] The layer the tip will be on.
     * \param dont_move_until[in] Until which dtt the branch should not move if possible.
     * \param roof[in] Whether the tip supports a roof.
     * \param skip_ovalisation[in] Whether the tip may be ovalized when drawn later.
     * \param additional_ovalization_targets[in] Additional targets the ovalization should reach.
     */
    TreeSupportElement*  addPointAsInfluenceArea(
        std::vector<std::set<TreeSupportElement*>>& move_bounds,
        std::pair<Point2LL, TreeSupportTipGenerator::LineStatus> p,
        size_t dtt,
        double hidden_radius_increase,
        LayerIndex insert_layer,
        size_t dont_move_until,
        bool roof,
        bool cradle,
        bool skip_ovalisation,
        std::vector<Point2LL> additional_ovalization_targets = std::vector<Point2LL>());


    /*!
     * \brief Add all points of a line as a tip
     * \param move_bounds[out] The storage for the tips.
     * \param lines[in] The lines of which points will be added.
     * \param roof_tip_layers[in] Amount of layers the tip should be drawn as roof.
     * \param insert_layer_idx[in] The layer the tip will be on.
     * \param tip_radius[in] Target radius of the tips.
     * \param supports_roof[in] Whether the tip supports a roof.
     * \param dont_move_until[in] Until which dtt the branch should not move if possible.
     * \param connect_points [in] If the points of said line should be connected by ovalization.
     */
    void addLinesAsInfluenceAreas(std::vector<std::set<TreeSupportElement *>>& move_bounds,
                                                              std::vector<TreeSupportTipGenerator::LineInformation> lines,
                                                              size_t roof_tip_layers,
                                                              LayerIndex insert_layer_idx,
                                                              coord_t tip_radius,
                                                              OverhangInformation& overhang_data,
                                                              size_t dont_move_until,
                                                              bool connect_points);

    /*!
     * \brief Remove tips that should not have been added in the first place.
     * \param move_bounds[in,out] The already added tips
     * \param storage[in] Background storage, required for adding roofs.
     * \param additional_support_areas[in] Areas that should have been roofs, but are now support, as they would not generate any lines as roof.
     */
    void removeUselessAddedPoints(std::vector<std::set<TreeSupportElement*>>& move_bounds, SliceDataStorage& storage, std::vector<Polygons>& additional_support_areas);

    /*!
     * \brief Contains config settings to avoid loading them in every function. This was done to improve readability of the code.
     */
    TreeSupportSettings config_;

    /*!
     * \brief If large areas should be supported by a roof out of regular support lines.
     */
    bool use_fake_roof_;

    /*!
     * \brief Generator for model collision, avoidance and internal guide volumes.
     */
    TreeModelVolumes& volumes_;

    /*!
     * \brief Minimum area an overhang has to have to be supported.
     */
    const double minimum_support_area_;

    /*!
     * \brief Minimum area an overhang has to have to become a roof.
     */
    const double minimum_roof_area_;

    /*!
     * \brief Amount of layers of roof. Zero if roof is disabled
     */
    const size_t support_roof_layers_;

    /*!
     * \brief Density the tips should have when supporting overhangs
     */
    const double support_tree_top_rate_;

    /*!
     * \brief Distance between support roof lines. Is required for generating roof patterns.
     */
    const coord_t support_roof_line_distance_;


    /*!
     * \brief Amount of offset to each overhang for support with regular branches (as opposed to roof).
     */
    const coord_t support_outset_;

    /*!
     * \brief Amount of offset to each overhang for support with roof (as opposed to regular branches).
     */
    const coord_t roof_outset_;

    /*!
     * \brief Whether tips should be printed as roof
     */
    const bool force_tip_to_roof_;

    /*!
     * \brief Whether the maximum distance a branch should from a point they support should be limited. Can be violated if required.
     */
    const bool support_tree_limit_branch_reach_;

    /*!
     * \brief Maximum distance a branch should from a point they support (in the xy plane). Can be violated if required.
     */
    const coord_t support_tree_branch_reach_limit_;

    /*!
     * \brief Distance in layers from the overhang to the first layer with support. This is the z distance in layers+1
     */
    const size_t z_distance_delta_;

    /*!
     * \brief Whether the Support Distance Priority is X/Y Overrides Z
     */
    const bool xy_overrides_;

    /*!
     * \brief Amount of layers further down than required an overhang can be supported, when Support Distance Priority is X/Y Overrides Z
     */
    size_t max_overhang_insert_lag_;

    /*!
     * \brief Area of a tip in mm2.
     */
    const double tip_roof_size_;

    /*!
     * \brief Whether only support that can rest on a flat surface should be supported.
     */
    const bool only_gracious_ = SUPPORT_TREE_ONLY_GRACIOUS_TO_MODEL;

    /*!
     * \brief Whether minimum_roof_area is a hard limit. If false the roof will be combined with roof above and below, to see if a part of this roof may be part of a valid roof
     * further up/down.
     */
    const bool force_minimum_roof_area_ = SUPPORT_TREE_MINIMUM_ROOF_AREA_HARD_LIMIT;

    /*!
     * \brief Distance between branches when the branches support a support pattern
     */
    coord_t support_supporting_branch_distance_;

    /*!
     * \brief Required to generate cross infill patterns. Key: Distance between lines
     */
    std::unordered_map<std::pair<coord_t,coord_t>, std::shared_ptr<SierpinskiFillProvider>> cross_fill_providers_;

    /*!
     * \brief Map that saves locations of already inserted tips. Used to prevent tips far to close together from being added.
     */
    std::vector<std::unordered_set<Point2LL>> already_inserted_;

    /*!
     * \brief Areas that will be saved as support roof
     */
    std::vector<Polygons> support_roof_drawn_;

    /*!
     * \brief Areas that will be saved as support roof
     */
    std::vector<Polygons> support_roof_drawn_fractional_;

    /*!
     * \brief Areas that will be saved as support roof, originating from tips being replaced with roof areas.
     */
    std::vector<Polygons> roof_tips_drawn_;


    std::vector<std::vector<TreeSupportCradle*>> cradle_data_;

    /*!
     * \brief Amount of layers of the cradle to support pointy overhangs.
     */
    size_t cradle_layers_;

    /*!
     * \brief Minimum amount of layers of the cradle to support pointy overhangs.
     */
    size_t cradle_layers_min_;

    /*!
     * \brief Amount of lines used for the cradle.
     */
    size_t cradle_line_count_;

    /*!
     * \brief Length of lines used for the cradle.
     */
    coord_t cradle_length_;

    /*!
     * \brief Minimum length of lines used for the cradle. TODO Width is effectively added to length ... fix or document?
     */
    coord_t cradle_length_min_;

    /*!
     * \brief Width of lines used for the cradle.
     */
    coord_t cradle_line_width_;

    /*!
     * \brief If cradle lines should be drawn as roof.
     */
    bool cradle_lines_roof_;

    /*!
     * \brief If the cradle base should be drawn as roof.
     */
    bool cradle_base_roof_;

    /*!
     * \brief If the (roof) cradle base should contain all cradle lines at cradle_tip_dtt size.
     */
    bool large_cradle_base_;


    /*!
     * \brief Maximum area of an overhang to still receive a cradle. Unit is square-microns!
     */
    double cradle_area_threshold_;

    /*!
     * \brief Distance to top of tips that support either the pointy overhang or the cradle lines at the bottom-most layer.
     */
    size_t cradle_tip_dtt_;

    /*!
     * \brief If the cradle lines should also be supported by larger tips.
     */
    bool large_cradle_line_tips_;

    /*!
     * \brief Distances the cradle lines should be from the model. First value corresponds to cradle line on the same layer as the first model line.
     */
    std::vector<coord_t> cradle_xy_distance_;

    /*!
     * \brief Distances in lines between the cradle and the support they are supported by.
     */
    size_t cradle_z_distance_layers_;

    std::mutex critical_cradle_;
    std::mutex critical_move_bounds_;
    std::mutex critical_roof_tips_;
    std::mutex critical_cross_fill_;

    mutable std::vector<std::vector<UnsupportedAreaInformation>> floating_parts_cache_;
    mutable std::vector<std::vector<std::vector<size_t>>> floating_parts_map_;
    std::unique_ptr<std::mutex> critical_floating_parts_cache_ = std::make_unique<std::mutex>();


};

} // namespace cura

#endif /* TREESUPPORTTIPGENERATOR_H */