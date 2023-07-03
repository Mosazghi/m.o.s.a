import { Prop, Schema, SchemaFactory } from '@nestjs/mongoose';
import { HydratedDocument } from 'mongoose';
import { ShoplistType } from '../type/shoplist.type';

export type Shoplists = HydratedDocument<Shoplist>;

@Schema()
export class Shoplist {
  @Prop({ required: true })
  bruker: string;

  @Prop({ required: true })
  dropSted: number;

  @Prop({ required: true, isnotempty: true })
  komponenter: ShoplistType[];
}

export const ShoplistSchema = SchemaFactory.createForClass(Shoplist);
